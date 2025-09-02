import pandas as pd
import pingouin as pg

# Cargar los datos
data = pd.read_csv("./data/CuestionarioEmpirica (respuestas) - Respuestas de formulario 1.csv", delimiter=',')

# Eliminar columnas innecesarias
data = data.drop(columns=['Puntuación', 'Dirección de correo electrónico', 'Marca temporal'])

# -------- Variables invertidas manualmente -------- #
invertir_items = [
    # Confidencialidad
    'Abro con frecuencia enlaces o archivos adjuntos en correos electrónicos de remitentes desconocidos.',
    'He abierto correos electrónicos identificados como spam en mi bandeja de entrada.',
    'He accedido a enlaces o archivos adjuntos provenientes de fuentes poco confiables o desconocidas.',
    
    # Integridad
    'Compartir datos en el ciberespacio no implica ningún riesgo',

    # Disponibilidad
    'Abro los archivos que descargo de Internet sin programa antivirus.'
]

# Invertir items (suponiendo escala de 1 a 5)
for col in invertir_items:
    data[col] = 6 - data[col]

# -------- Definir constructos -------- #
constructos = {
    'Confidencialidad': [
        'Soy prudente con la información personal que comparto en el ciberespacio.',
        'Me aseguro de que los datos que comparto en el ciberespacio sólo pueden ser gestionados por la persona con acceso.',
        'Me preocupa compartir mis datos de contacto en el ciberespacio.',
        'Abro con frecuencia enlaces o archivos adjuntos en correos electrónicos de remitentes desconocidos.',
        'Considero que usar páginas web sin certificado de seguridad actualizado es perjudicial.',
        'He abierto correos electrónicos identificados como spam en mi bandeja de entrada.',
        'He accedido a enlaces o archivos adjuntos provenientes de fuentes poco confiables o desconocidas.'
    ],
    'Integridad': [
        'Me preocupa que mis datos almacenados en línea puedan ser alterados sin mi consentimiento.',
        'Compartir datos en el ciberespacio no implica ningún riesgo',
        'Siempre verifico la fuente de la información antes de reenviarla o modificarla.',
        'La información y los documentos que he almacenado en el ciberespacio pueden perderse o eliminarse'
    ],
    'Disponibilidad': [
        'Mantengo actualizado mi programa antivirus en mi dispositivo.',
        'Escaneo regularmente mi dispositivo con un programa antivirus.',
        'Mantengo activado el cortafuegos (firewall) en mi dispositivo como una medida de protección frente a accesos no autorizados.',
        'Abro los archivos que descargo de Internet sin programa antivirus.',
        'Hago copias de seguridad de mi información.'
    ]
}

# -------- Análisis ítem-total -------- #
def analisis_item_total(nombre, df_constructo):
    print(f"\n🧠 Análisis ítem-total para: {nombre}")
    alfa_total, _ = pg.cronbach_alpha(df_constructo)
    print(f"Alfa total: {alfa_total:.3f}")

    for col in df_constructo.columns:
        df_tmp = df_constructo.drop(columns=[col])
        alfa, _ = pg.cronbach_alpha(df_tmp)
        correlaciones = df_constructo.corrwith(df_constructo.sum(axis=1) - df_constructo[col])
        print(f"\nÍtem: {col}")
        print(f"  Alfa si se elimina: {alfa:.3f}")
        print(f"  Correlación ítem-total corregida: {correlaciones[col]:.3f}")

# Ejecutar análisis por constructo
for nombre, columnas in constructos.items():
    sub_df = data[columnas].copy()
    analisis_item_total(nombre, sub_df)
