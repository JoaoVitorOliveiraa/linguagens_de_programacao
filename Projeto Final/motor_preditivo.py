import joblib
import numpy as np
import pandas as pd

# Carrega o modelo e TODOS os transformadores salvos
try:
    MODELO = joblib.load('melhor_modelo_otimizado.pkl')
    ENCODER = joblib.load('encoder.pkl')
    ORDINAL = joblib.load('ordinal_encoder.pkl')
    POWER = joblib.load('power.pkl')
    SCALER = joblib.load('scaler.pkl')
    PCA = joblib.load('pca.pkl')
    ERRO_CARREGAMENTO = None
except Exception as e:
    MODELO = None
    ERRO_CARREGAMENTO = str(e)

def processar_e_prever(dados_string):
    if MODELO is None:
        return f"Erro: Modelo nao encontrado. Detalhe: {ERRO_CARREGAMENTO}"

    try:
        partes = dados_string.split(',')
        
        # =========================================================
        # CASO 1: SIMPLIFICADO (5 dados)
        # =========================================================
        if len(partes) == 5:
            renda = float(partes[0])
            gasto_atual = float(partes[1])
            score = float(partes[2])
            categoria = partes[3]
            estresse = partes[4]

            # Estima o resto
            dados = pd.DataFrame([{
                'monthly_income': renda,
                'credit_score': score,
                'savings_rate': 0.1,
                'budget_goal': renda * 0.8,
                'financial_scenario': 'normal',
                'debt_to_income_ratio': 0.3,
                'loan_payment': renda * 0.1,
                'investment_amount': renda * 0.05,
                'subscription_services': 3,
                'emergency_fund': 1000.0,
                'transaction_count': 30,
                'fraud_flag': 0,
                'income_type': 'Salary',
                'rent_or_mortgage': renda * 0.3,
                'category': categoria,
                'cash_flow_status': 'Positive',
                'financial_advice_score': 50.0,
                'financial_stress_level': estresse
            }])
        
        # =========================================================
        # CASO 2: DETALHADO (19 dados)
        # =========================================================
        else:
            renda = float(partes[0])
            gasto_atual = float(partes[1])
            score = float(partes[2])
            categoria = partes[3]
            estresse = partes[4]
            savings = float(partes[5])
            budget = float(partes[6])
            scenario = partes[7]
            dirt = float(partes[8])
            loan = float(partes[9])
            invest = float(partes[10])
            subs = int(partes[11])
            fund = float(partes[12])
            trans = int(partes[13])
            inc_type = partes[14]
            rent = float(partes[15])
            flow = partes[16]
            advice = float(partes[17])
            fraud = int(partes[18])

            dados = pd.DataFrame([{
                'monthly_income': renda,
                'credit_score': score,
                'savings_rate': savings,
                'budget_goal': budget,
                'financial_scenario': scenario,
                'debt_to_income_ratio': dirt,
                'loan_payment': loan,
                'investment_amount': invest,
                'subscription_services': subs,
                'emergency_fund': fund,
                'transaction_count': trans,
                'fraud_flag': fraud,
                'income_type': inc_type,
                'rent_or_mortgage': rent,
                'category': categoria,
                'cash_flow_status': flow,
                'financial_advice_score': advice,
                'financial_stress_level': estresse
            }])

        # =========================================================
        # TRANSFORMAÇÃO (mesma ordem do treinamento)
        # =========================================================
        
        # 1. Nominais (OneHot)
        cols_nominais = ['financial_scenario', 'income_type', 'category', 'cash_flow_status']
        enc_nom = ENCODER.transform(dados[cols_nominais])
        df_nom = pd.DataFrame(enc_nom, columns=ENCODER.get_feature_names_out(cols_nominais))
        
        # 2. Ordinais
        cols_ordinais = ['financial_stress_level']
        enc_ord = ORDINAL.transform(dados[cols_ordinais]).astype(float)
        df_ord = pd.DataFrame(enc_ord, columns=cols_ordinais)

        # 3. Cauda Longa (Power)
        cols_cauda_longa = ['investment_amount', 'emergency_fund', 'rent_or_mortgage']
        enc_power = POWER.transform(dados[cols_cauda_longa])
        df_power = pd.DataFrame(enc_power, columns=cols_cauda_longa)

        # 4. Numéricas Normais
        cols_normais = [
            'monthly_income', 'credit_score', 'debt_to_income_ratio', 'loan_payment',
            'subscription_services', 'transaction_count', 'financial_advice_score',
            'savings_rate', 'budget_goal', 'fraud_flag'
        ]

        # 5. Junta tudo na ordem exata do treinamento e escala
        df_para_escalar = pd.concat([dados[cols_normais], df_ord, df_nom], axis=1)
        enc_scaled = SCALER.transform(df_para_escalar)
        
        # 6. Junta com Power e aplica PCA
        df_final = np.hstack((enc_scaled, df_power.values))
        final_pca = PCA.transform(df_final)

        # =========================================================
        # PREVISÃO
        # =========================================================
        previsao = MODELO.predict(final_pca)[0]
        previsao = max(0.0, previsao) 
        
        diferenca = previsao - gasto_atual
        if diferenca > 0:
            tendencia = f"ALTA (+ R$ {diferenca:.2f})"
        elif diferenca < 0:
            tendencia = f"QUEDA (- R$ {abs(diferenca):.2f})"
        else:
            tendencia = "ESTAVEL"

        return f"Previsao: R$ {previsao:.2f} | Tendencia: {tendencia}"

    except Exception as e:
        return f"Erro na previsao: {str(e)}"