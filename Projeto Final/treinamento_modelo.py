# =====================================================================
# Importação das bibliotecas.
# =====================================================================

import joblib
import pandas as pd
from sklearn.svm import SVR
from funcoes_analise_dados import *
from sklearn.pipeline import make_pipeline
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.preprocessing import OrdinalEncoder, StandardScaler, OneHotEncoder, PowerTransformer, PolynomialFeatures

# =====================================================================
# Carregando e limpando os dados.
# =====================================================================

dados = pd.read_csv('personal_finance_tracker_dataset.csv')
dados = dados.drop(columns=['date', 'user_id'])

# =====================================================================
# Análise exploratória dos dados.
# =====================================================================

# 1. Histogramas: Para descobrir quais colunas têm cauda longa.
exibir_histogramas(dados, bins=15, n_colunas_grade=2)

# 2. Correlações: Para descobrir quais variáveis têm relação com o alvo.
#show_correlations(dados, "monthly_expense_total")

# 3. Matriz de Correlação: Para ver a relação entre todas as variáveis.
#show_correlation_matrix(dados, method='spearman')

# =====================================================================
# Separarando o Target (y) e Features (X).
# =====================================================================

y = dados['monthly_expense_total']

# =====================================================================
# Removendo colunas que causam vazamento de informação para o modelo.
# =====================================================================

colunas_com_vazamento = ['discretionary_spending', 'essential_spending', 'actual_savings', 'savings_goal_met']
X = dados.drop(columns=['monthly_expense_total'] + colunas_com_vazamento)

# =====================================================================
# Dividindo as amostras de treino e teste.
# =====================================================================

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=30)

# =====================================================================
# Aplicando OneHotEncoder nas colunas nominais.
# =====================================================================

colunas_nominais = ['financial_scenario', 'income_type', 'category', 'cash_flow_status']
one_hot_encoder = OneHotEncoder(sparse_output=False, handle_unknown='ignore')
X_train_encoded = one_hot_encoder.fit_transform(X_train[colunas_nominais])
X_test_encoded = one_hot_encoder.transform(X_test[colunas_nominais]) 

# Transformando em DataFrame para facilitar o manuseio.
nomes_colunas_one_hot = one_hot_encoder.get_feature_names_out(colunas_nominais)
df_train_one_hot = pd.DataFrame(X_train_encoded, columns=nomes_colunas_one_hot, index=X_train.index)
df_test_one_hot = pd.DataFrame(X_test_encoded, columns=nomes_colunas_one_hot, index=X_test.index)

# =====================================================================
# Aplicando OrdinalEncoder nas colunas ordinais.
# =====================================================================

# Para a feacture 'financial_stress_level': Baixo=0, Médio=1, Alto=2.
colunas_ordinais = ['financial_stress_level']
ordem_correta = [['Low', 'Medium', 'High']] 
ordinal_encoder = OrdinalEncoder(categories=ordem_correta)

# O .astype(float) garante que o resultado seja numérico
X_train_ord = ordinal_encoder.fit_transform(X_train[colunas_ordinais]).astype(float)
X_test_ord = ordinal_encoder.transform(X_test[colunas_ordinais]).astype(float) 

# Transformando em DataFrame para facilitar o manuseio.
df_train_ord = pd.DataFrame(X_train_ord, columns=colunas_ordinais, index=X_train.index)
df_test_ord = pd.DataFrame(X_test_ord, columns=colunas_ordinais, index=X_test.index)

# =================================================================================
# Aplicando PowerTransformer, com o método 'yeo-johnson', nas colunas assimétricas.
# =================================================================================

colunas_cauda_longa = ['investment_amount', 'emergency_fund', 'rent_or_mortgage']
power_transformer = PowerTransformer(method='yeo-johnson')
X_train_power = power_transformer.fit_transform(X_train[colunas_cauda_longa])
X_test_power = power_transformer.transform(X_test[colunas_cauda_longa])

# Transformando em DataFrame para facilitar o manuseio.
df_train_power = pd.DataFrame(X_train_power, columns=colunas_cauda_longa, index=X_train.index)
df_test_power = pd.DataFrame(X_test_power, columns=colunas_cauda_longa, index=X_test.index)

# ===========================================================================
# Aplicando StandardScaler nas colunas numéricas normais, ordinais e one_hot.
# ===========================================================================

colunas_normais = [
    'monthly_income', 
    'credit_score', 
    'debt_to_income_ratio', 
    'loan_payment', 
    'subscription_services', 
    'transaction_count', 
    'financial_advice_score', 
    'savings_rate',       
    'budget_goal',        
    'fraud_flag'          
]

# df_train_para_escalar = pd.concat([X_train[colunas_normais + colunas_ordinais], df_train_one_hot], axis=1)
# df_test_para_escalar = pd.concat([X_test[colunas_normais + colunas_ordinais], df_test_one_hot], axis=1)

df_train_para_escalar = pd.concat([X_train[colunas_normais], df_train_ord, df_train_one_hot], axis=1)
df_test_para_escalar = pd.concat([X_test[colunas_normais], df_test_ord, df_test_one_hot], axis=1)

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(df_train_para_escalar)
X_test_scaled = scaler.transform(df_test_para_escalar) 

# =====================================================================
# Juntando os dados e aplicando PCA.
# =====================================================================

X_train_final = np.hstack((X_train_scaled, df_train_power.values))
X_test_final = np.hstack((X_test_scaled, df_test_power.values))

# Aplica o PCA mantendo 95% da variância explicada dos dados.
X_train_pca, X_test_pca, pca = aplicar_pca(X_train_final, X_test_final, n_componentes=0.95)

print(f"Features originais antes do PCA: {X_train_final.shape[1]}")
print(f"Componentes após PCA: {pca.n_components_}")

# =====================================================================
# Salvando os transformadores (já ajustados no fit_transform).
# =====================================================================

joblib.dump(one_hot_encoder, 'encoder.pkl')
joblib.dump(ordinal_encoder, 'ordinal_encoder.pkl')
joblib.dump(power_transformer, 'power.pkl')
joblib.dump(scaler, 'scaler.pkl')
joblib.dump(pca, 'pca.pkl')
print("\nTransformadores salvos com sucesso! Iniciando otimização...\n")

# =====================================================================
# Treinando e comparando os modelos.
# =====================================================================

# Otimização de hiperparâmetros.
configuracoes = {
    "Regressão Linear": {
        "modelo": LinearRegression(),
        "grade": {},
    },
    "Polinomial L1 (Lasso)": {
        "modelo": make_pipeline(PolynomialFeatures(), Lasso(max_iter=50000, tol=0.01)),
        "grade": {
            "polynomialfeatures__degree": [1, 2, 3],
            "lasso__alpha": [0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0],
        },
    },
    "Polinomial L2 (Ridge)": {
        "modelo": make_pipeline(PolynomialFeatures(), Ridge()),
        "grade": {
            "polynomialfeatures__degree": [1, 2, 3],
            "ridge__alpha": [0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0, 1000.0, 10000.0],
        },
    },
    "Random Forest": {
        "modelo": RandomForestRegressor(random_state=30, n_jobs=-1),
        "grade": {
            "n_estimators": [100, 200, 300],
            "max_depth": [None, 10, 20, 30],
            "min_samples_split": [2, 5, 10],
            "min_samples_leaf": [1, 2, 4],
        },
    },
    "SVR": {
        "modelo": SVR(),
        "grade": {
            "kernel": ["rbf", "linear"],
            "C": [0.001, 0.01, 0.1, 1, 10, 100],
            "epsilon": [0.01, 0.1, 0.5],
            "gamma": ["scale", "auto"],
        },
    },
}

resultados_otimizados = otimizar_e_comparar_modelos(
    configuracoes,
    X_train_pca, y_train,
    X_test_pca, y_test,
)

# =====================================================================
# Salvando o melhor modelo otimizado (após o treinamento).
# =====================================================================

melhor_nome = min(
    resultados_otimizados,
    key=lambda k: resultados_otimizados[k]["rmse_teste"]
)
melhor_modelo = resultados_otimizados[melhor_nome]["melhor_modelo"]

joblib.dump(melhor_modelo, 'melhor_modelo_otimizado.pkl')
print(f"\nMelhor modelo ({melhor_nome}) salvo em 'melhor_modelo_otimizado.pkl'")