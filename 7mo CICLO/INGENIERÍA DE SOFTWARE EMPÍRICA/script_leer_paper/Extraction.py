import re
import pdfplumber

# Lista de palabras a buscar
palabras = ["classification", "clustering", "prediction", "real time detection", "geometry",
            "physical spaces", "physical environment", "experience based design", "EGG", "EMG",
            "EOG", "HVR", "fMRI", "GRS", "PPG", "RR", "SKT", "FE", "BP", "GA", "IROG", "VOG", "SKT",
            "rPPG", "proximity", "similarity", "gigure and ground", "spatial cognition", "closure",
            "continuity", "symmetry", "visual point", "color", "complexity", "proportion", "order",
            "russel’s circumplex model", "dimensional models", "discrete categories"
]

# Expresión regular tipo OR, insensible a mayúsculas
patron = re.compile(r'\b(?:' + '|'.join(palabras) + r')\b', re.IGNORECASE)

# Diccionario para guardar los resultados
resultados = {}

# Abrir el PDF
with pdfplumber.open("./pdfs/101.pdf") as pdf:
    for i, pagina in enumerate(pdf.pages):
        texto = pagina.extract_text()
        if texto:
            coincidencias = list(patron.finditer(texto))
            if coincidencias:
                fragmentos = []
                for match in coincidencias:
                    palabra_encontrada = match.group()
                    # Contexto alrededor de la coincidencia
                    inicio = max(match.start() - 100, 0)
                    fin = min(match.end() + 100, len(texto))
                    contexto = texto[inicio:fin].replace('\n', ' ')
                    fragmentos.append({
                        "palabra": palabra_encontrada,
                        "contexto": contexto.strip()
                    })
                resultados[f"Página {i + 1}"] = fragmentos

# Mostrar resultados
for pagina, fragmentos in resultados.items():
    print(f"\n{pagina}:")
    for frag in fragmentos:
        print(f" - Palabra: {frag['palabra']}")
        print(f"   Contexto: {frag['contexto']}")
