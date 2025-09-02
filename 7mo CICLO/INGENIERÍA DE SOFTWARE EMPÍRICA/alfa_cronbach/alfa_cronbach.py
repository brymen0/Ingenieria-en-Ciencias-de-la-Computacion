import pandas as pd
import pingouin as pg

# Cargar los datos
data = pd.read_csv("./data/CuestionarioEmpirica (respuestas) - Respuestas de formulario 1.csv", delimiter=',')

# Eliminar columnas innecesarias
data = data.drop(columns=['Puntuación', 'Dirección de correo electrónico', 'Marca temporal'])

# Escala invertida: de 1 a 5
invertir = lambda x: 6 - x

# CONFIDENCIALIDAD
confidencialidad = data[
    ['Soy prudente con la información personal que comparto en el ciberespacio.',
     'Me aseguro de que los datos que comparto en el ciberespacio sólo pueden ser gestionados por la persona con acceso.',
     'Me preocupa compartir mis datos de contacto en el ciberespacio.',
     'Abro con frecuencia enlaces o archivos adjuntos en correos electrónicos de remitentes desconocidos.',
     'Considero que usar páginas web sin certificado de seguridad actualizado es perjudicial.',
     'He abierto correos electrónicos identificados como spam en mi bandeja de entrada.',
     'He accedido a enlaces o archivos adjuntos provenientes de fuentes poco confiables o desconocidas.'
    ]
].copy()

confidencialidad.rename(columns={
    'Soy prudente con la información personal que comparto en el ciberespacio.': 'C1',
    'Me aseguro de que los datos que comparto en el ciberespacio sólo pueden ser gestionados por la persona con acceso.': 'C2',
    'Me preocupa compartir mis datos de contacto en el ciberespacio.': 'C3',
    'Abro con frecuencia enlaces o archivos adjuntos en correos electrónicos de remitentes desconocidos.': 'C4',
    'Considero que usar páginas web sin certificado de seguridad actualizado es perjudicial.': 'C5',
    'He abierto correos electrónicos identificados como spam en mi bandeja de entrada.': 'C6',
    'He accedido a enlaces o archivos adjuntos provenientes de fuentes poco confiables o desconocidas.': 'C7'
}, inplace=True)

# Invertir ítems negativos en confidencialidad
confidencialidad['C4'] = confidencialidad['C4'].apply(invertir)
confidencialidad['C6'] = confidencialidad['C6'].apply(invertir)
confidencialidad['C7'] = confidencialidad['C7'].apply(invertir)

# INTEGRIDAD
integridad = data[
    [
        'Me preocupa que mis datos almacenados en línea puedan ser alterados sin mi consentimiento.',
        'Compartir datos en el ciberespacio no implica ningún riesgo',
        'Siempre verifico la fuente de la información antes de reenviarla o modificarla.',
        'La información y los documentos que he almacenado en el ciberespacio pueden perderse o eliminarse'
    ]
].copy()

integridad.rename(columns={
    'Me preocupa que mis datos almacenados en línea puedan ser alterados sin mi consentimiento.': 'I1',
    'Compartir datos en el ciberespacio no implica ningún riesgo': 'I2',
    'Siempre verifico la fuente de la información antes de reenviarla o modificarla.': 'I3',
    'La información y los documentos que he almacenado en el ciberespacio pueden perderse o eliminarse': 'I4'
}, inplace=True)

# Invertir ítem negativo en integridad
integridad['I2'] = integridad['I2'].apply(invertir)

# DISPONIBILIDAD
disponibilidad = data[
    [
        'Mantengo actualizado mi programa antivirus en mi dispositivo.',
        'Escaneo regularmente mi dispositivo con un programa antivirus.',
        'Mantengo activado el cortafuegos (firewall) en mi dispositivo como una medida de protección frente a accesos no autorizados.',
        'Abro los archivos que descargo de Internet sin programa antivirus.',
        'Hago copias de seguridad de mi información.'
    ]
].copy()

disponibilidad.rename(columns={
    'Mantengo actualizado mi programa antivirus en mi dispositivo.': 'D1',
    'Escaneo regularmente mi dispositivo con un programa antivirus.': 'D2',
    'Mantengo activado el cortafuegos (firewall) en mi dispositivo como una medida de protección frente a accesos no autorizados.': 'D3',
    'Abro los archivos que descargo de Internet sin programa antivirus.': 'D4',
    'Hago copias de seguridad de mi información.': 'D5'
}, inplace=True)

# Invertir ítem negativo en disponibilidad
disponibilidad['D4'] = disponibilidad['D4'].apply(invertir)

# Función de estadísticas
def estadisticas_constructo(constructo):
    print(constructo.corr())
    print(constructo.describe())
    print(f'Alfa de Cronbach: {pg.cronbach_alpha(data=constructo)[0]:.3f}')

# Imprimir resultados
print("Confidencialidad")
estadisticas_constructo(confidencialidad)
print("\nIntegridad")
estadisticas_constructo(integridad)
print("\nDisponibilidad")
estadisticas_constructo(disponibilidad)
