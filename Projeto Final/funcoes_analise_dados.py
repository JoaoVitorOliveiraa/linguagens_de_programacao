# =====================================================================
# Importação das bibliotecas.
# =====================================================================

import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from scipy.stats import pearsonr, kendalltau, spearmanr
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.model_selection import GridSearchCV, KFold, cross_val_score

# =====================================================================
# Declaração das funções.
# =====================================================================
               
def show_correlations(data, target, columns=False):
    """
    Exibe coeficientes de Pearson e Kendall Tau com p-values
    entre as colunas fornecidas e o alvo 'target'.
    
    Parâmetros:
    - data: DataFrame com os dados.
    - target: string com o nome da coluna alvo.
    - columns: lista de colunas a analisar (opcional). Se False, usa todas.
    """
    
    if columns:
        columns_list = columns

    else:
        columns_list = list(data.columns)

    print(" ")
    print("COMPARAÇÃO DE CORRELAÇÃO COM O ALVO:", target)
    print(" ")
    print(f"{'Variável':<33} {'Pearson':<12} {'P-Value':<10} {'Kendall':<12} {'P-Value':<10} {'Spearman':<12} {'P-Value'}")
    print("-" * 102)

    for column in columns_list:
        coef_pearsonr, p_value_pearsonr = pearsonr(data[column], data[target])
        coef_kendalltau, p_value_kendalltau = kendalltau(data[column], data[target])
        coef_spearmanr, p_value_spearmanr = spearmanr(data[column], data[target])
        print(f"{column:<30} {coef_pearsonr:10.4f} {p_value_pearsonr:12.5f} {coef_kendalltau:10.4f} {p_value_kendalltau:12.5f} {coef_spearmanr:10.4f} {p_value_spearmanr:12.5f} ")
        
        
def show_correlation_matrix(data, method='spearman'):
    """
    Exibe a matriz de correlação entre as variáveis do conjunto de dados.
    """
    
    # Calculando matriz de correlação (Spearman por padrão).
    corr_matrix = data.corr(method=method)
    
    # Gerando o heatmap.
    plt.figure(figsize=(12, 12))
    heatmap = sns.heatmap(
        corr_matrix,
        annot=True,            # Mostra valores nas células
        fmt=".2f",             # Formato com 2 casas decimais
        cmap='coolwarm',       # Mapa de cores (azul-quente)
        center=0,              # Centraliza o branco no 0
        vmin=-1,               # Valor mínimo da escala
        vmax=1,                # Valor máximo da escala
        linewidths=.5,         # Largura das linhas entre células
        square=True            # Mantém as células quadradas
    )
    
    # Ajustando título e labels.
    plt.title(f'Matriz de Correlação ({method.title()})', fontsize=14, pad=20)
    heatmap.set_xticklabels(
        heatmap.get_xticklabels(),
        rotation=45,
        horizontalalignment='right'
    )
    
    # Mostrando o gráfico.
    plt.tight_layout()
    plt.show()
    
    
def exibir_histogramas(df, bins=30, n_colunas_grade=3, colunas=None):
    """
    Função que:
        -Exibe um histograma para cada coluna numérica de um DataFrame
        -Organiza todos os histogramas em uma única figura
        -Ajusta dinamicamente o layout com base no número de colunas
    """
    
    # Se o usuário não fornecer colunas, seleciona todas as colunas numéricas automaticamente.
    if colunas is None:
        colunas = df.select_dtypes(include=np.number).columns.tolist()

    n_colunas_plotadas = len(colunas)
    n_linhas_grade = int(np.ceil(n_colunas_plotadas / n_colunas_grade))
    plt.figure(figsize=(6 * n_colunas_grade, 4 * n_linhas_grade))

    for i, coluna in enumerate(colunas):
        ax = plt.subplot(n_linhas_grade, n_colunas_grade, i + 1)
        ax.hist(df[coluna].dropna(), bins=bins, color='skyblue', edgecolor='black')
        ax.set_title(coluna)
        ax.set_xlabel("Valor")
        ax.set_ylabel("Frequência")

    plt.tight_layout()
    plt.show()


def aplicar_pca(X_train, X_test, n_componentes=0.95):
    """
    Aplica PCA no conjunto de treino e transforma o treino e o teste.
    Gera gráficos de variância explicada para análise.

    Retorna:
    - X_train_pca: dados de treino transformados
    - X_test_pca: dados de teste transformados
    - modelo_pca: o objeto PCA ajustado
    """
    # 1. Instancia e treina o PCA APENAS no treino
    pca = PCA(n_components=n_componentes)
    X_train_pca = pca.fit_transform(X_train)
    X_test_pca = pca.transform(X_test) # Apenas transforma o teste

    var_explicada = pca.explained_variance_ratio_

    # 2. Gráfico da variância explicada por componente
    plt.figure(figsize=(10, 5))
    plt.bar(range(1, len(var_explicada) + 1), var_explicada, alpha=0.7)
    plt.ylabel('Variância explicada %')
    plt.xlabel('Componentes do PCA')
    plt.title('Variância explicada por componente')
    plt.grid(True)
    plt.show()

    # 3. Gráfico da variância acumulada
    plt.figure(figsize=(10, 5))
    plt.plot(range(1, len(var_explicada) + 1), np.cumsum(var_explicada),
             marker='o', color='brown')
    plt.ylabel('Variância explicada acumulada %')
    plt.xlabel('Número de componentes do PCA')
    plt.title('Soma acumulada da variância explicada')
    plt.grid(True)
    plt.axhline(y=0.95, color='r', linestyle='--', label='95% de variância') # Linha de referência
    plt.legend()
    plt.show()

    return X_train_pca, X_test_pca, pca


def otimizar_e_comparar_modelos(configuracoes, X_train, y_train, X_test, y_test,
                                 cv_folds=5, scoring='neg_root_mean_squared_error'):
    """
    Otimiza hiperparâmetros de vários modelos via GridSearchCV + K-Fold,
    re-treina o melhor estimador de cada um no conjunto completo de treino,
    avalia no teste e exibe uma tabela comparativa final.

    Parâmetros
    ----------
    configuracoes : dict
        Dicionário no formato:
        {
            "Nome do Modelo": {
                "modelo": estimator (ou Pipeline),
                "grade": {param: [valores]}  # {} se não houver o que otimizar
            },
            ...
        }
    X_train, y_train : arrays
        Conjunto de treino JÁ transformado (PCA incluído, se for o caso).
    X_test, y_test : arrays
        Conjunto de teste, usado só para avaliação final.
    cv_folds : int
        Número de folds da validação cruzada.
    scoring : str
        Métrica de avaliação (padrão: RMSE negativo, porque sklearn maximiza).

    Retorna
    -------
    dict : resultados no formato
        {
            "Nome do Modelo": {
                "melhor_modelo": estimator,
                "melhores_params": dict,
                "rmse_cv": float,
                "rmse_teste": float,
                "r2_teste": float,
            },
            ...
        }
    """

    cv = KFold(n_splits=cv_folds, shuffle=True, random_state=30)
    resultados = {}

    print(" ")
    print("OTIMIZAÇÃO DE HIPERPARÂMETROS")
    print(" ")

    # -----------------------------------------------------------------
    # 1) Loop de otimização + treino final.
    # -----------------------------------------------------------------
    for nome, cfg in configuracoes.items():
        modelo = cfg["modelo"]
        grade = cfg["grade"]

        print(f"[{nome}]")

        # Caso especial: modelo sem hiperparâmetros (ex: LinearRegression)
        if not grade:
            print("  - Sem hiperparâmetros — treinando direto.")
            modelo.fit(X_train, y_train)

            scores_cv = cross_val_score(modelo, X_train, y_train,
                                        cv=cv, scoring=scoring)
            rmse_cv = -scores_cv.mean()
            melhores_params = {}
            melhor_modelo = modelo

        else:
            n_combinacoes = int(np.prod([len(v) for v in grade.values()]))
            print(f"  - Testando {n_combinacoes} combinações x {cv_folds} folds...")

            grid = GridSearchCV(
                estimator=modelo,
                param_grid=grade,
                cv=cv,
                scoring=scoring,
                n_jobs=-1,
                verbose=0,
                refit=True,   # re-treina o melhor no dataset completo de treino
            )
            grid.fit(X_train, y_train)

            melhor_modelo = grid.best_estimator_
            melhores_params = grid.best_params_
            rmse_cv = -grid.best_score_

        # Avaliação final no conjunto de teste
        previsoes = melhor_modelo.predict(X_test)
        rmse_teste = np.sqrt(mean_squared_error(y_test, previsoes))
        r2_teste = r2_score(y_test, previsoes)

        resultados[nome] = {
            "melhor_modelo": melhor_modelo,
            "melhores_params": melhores_params,
            "rmse_cv": rmse_cv,
            "rmse_teste": rmse_teste,
            "r2_teste": r2_teste,
        }

        print(f"  - Melhores parâmetros: {melhores_params or '(nenhum)'}")
        print(f"  - RMSE (CV):    R$ {rmse_cv:.2f}")
        print(f"  - RMSE (teste): R$ {rmse_teste:.2f}")
        print(f"  - R²   (teste):    {r2_teste:.4f}")
        print(" ")

    # -----------------------------------------------------------------
    # 2) Tabela comparativa final.
    # -----------------------------------------------------------------
    ordenados = sorted(resultados.items(), key=lambda x: x[1]["rmse_teste"])

    print(" ")
    print("COMPARAÇÃO DE MODELOS OTIMIZADOS (ordenado por RMSE de teste)")
    print(" ")
    print(f"{'Modelo':<28} {'RMSE (teste)':>14} {'R² (teste)':>12} "
          f"{'RMSE (CV)':>13} {'Melhores Parâmetros'}")
    print("-" * 130)

    for nome, res in ordenados:
        params_str = ", ".join(
            f"{k}={v}" for k, v in res["melhores_params"].items()
        ) if res["melhores_params"] else "(nenhum)"

        print(f"{nome:<28} "
              f"R$ {res['rmse_teste']:>10.2f}   "
              f"{res['r2_teste']:>10.4f}   "
              f"R$ {res['rmse_cv']:>8.2f}   "
              f"{params_str}")

    print("-" * 130)

    melhor_nome = ordenados[0][0]
    print(f"\nMelhor modelo: {melhor_nome}")
    print(f"  RMSE (teste): R$ {ordenados[0][1]['rmse_teste']:.2f}")
    print(f"  R²   (teste): {ordenados[0][1]['r2_teste']:.4f}")

    return resultados