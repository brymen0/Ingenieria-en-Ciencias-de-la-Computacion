import pygame, random
from view.View import View
from model.constantes import FPS, POSICION_IMG_ASIENTOS, ESTADOS_ALFOMBRA, TIEMPO_MAX, TIEMPO_MIN
from model.Asiento import Asiento
from view.SpriteAsiento import SpriteAsiento
from view.SpritePersona import SpritePersona

class MainController:
    def __init__(self):
        pygame.init()
        self.vista = View(1300, 700)
        self.alfombra_ocupada = [False, False, False]  
        self.creando_persona = False
        self.personas_buscando_puesto = pygame.sprite.Group()
        self.sprite_asientos = []
        self.generarAsientos()
        self.tiempo_siguiente_llegada = pygame.time.get_ticks() + random.randint(100, 150)

    def run (self) :
        reloj = pygame.time.Clock()
        done = False
        while not done:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True
                if event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = event.pos
                    print(f"Click en: ({x}, {y})")
            self.update()
            reloj.tick(FPS)

    def update(self):
        tiempo_ultimo_generado = pygame.time.get_ticks()
        self.entraNuevaPersona(tiempo_ultimo_generado)
        self.avanzar_alfombra()

        self.personas_buscando_puesto.update()
        self.vista.dibujar([self.personas_buscando_puesto, self.sprite_asientos])

    '''def entraNuevaPersona(self, tiempo_ultimo_generado):
        if not self.creando_persona and tiempo_ultimo_generado >= self.tiempo_siguiente_llegada and not self.alfombra_ocupada[0]:
            self.creando_persona = True
            print("Generando nueva persona en el primer estado de la alfombra")
            new_person = SpritePersona()
            self.personas_buscando_puesto.add(new_person)
            new_person.actualizar_destino([ESTADOS_ALFOMBRA[0]])
            
            # Marcar el primer estado como ocupado
            self.alfombra_ocupada[0] = new_person
            self.creando_persona =  False
            
            # Definir el tiempo para la siguiente llegada
            self.tiempo_siguiente_llegada = tiempo_ultimo_generado + random.randint(TIEMPO_MIN, TIEMPO_MAX)'''
    
    def entraNuevaPersona(self, tiempo_ultimo_generado):
        if not self.creando_persona and tiempo_ultimo_generado >= self.tiempo_siguiente_llegada and not self.alfombra_ocupada[0]:
            self.creando_persona = True
            print("Generando nueva persona en el primer estado de la alfombra")
            new_person = SpritePersona()

            # Buscar asiento libre
            asiento_libre = None
            for sprite in self.sprite_asientos:
                if sprite.asiento.esta_libre():
                    asiento_libre = sprite.asiento
                    break

            if not asiento_libre:
                print("No hay asientos disponibles")
                self.creando_persona = False
                return

            new_person.asiento_asignado = asiento_libre
            new_person.destino_final = asiento_libre.coordenadas_atencion

            # Determinar destino_fila (estado intermedio)
            id_asiento = asiento_libre.id
            if id_asiento in {1, 2, 3, 10, 11, 12}:
                new_person.destino_fila = ESTADOS_ALFOMBRA[2]
            elif id_asiento in {4, 5, 6, 13, 14, 15}:
                new_person.destino_fila = ESTADOS_ALFOMBRA[1]
            else:
                new_person.destino_fila = ESTADOS_ALFOMBRA[0]

            new_person.actualizar_destino([ESTADOS_ALFOMBRA[0]])
            self.personas_buscando_puesto.add(new_person)
            self.alfombra_ocupada[0] = new_person
            self.creando_persona = False
            self.tiempo_siguiente_llegada = tiempo_ultimo_generado + random.randint(TIEMPO_MIN, TIEMPO_MAX)



    '''def avanzar_alfombra(self):
        for i in range(len(self.alfombra_ocupada) - 1, -1, -1): 
            if self.alfombra_ocupada[i]:  # Si hay una persona en este estado
                persona = self.alfombra_ocupada[i]
                estado_siguiente = ESTADOS_ALFOMBRA[i+1] if i+1 < len(ESTADOS_ALFOMBRA) else None

                if estado_siguiente:
                    # Diccionario con tuplas como claves
                    asientos_estado_siguiente = {
                        tuple(ESTADOS_ALFOMBRA[0]): {1, 2, 3, 10, 11, 12},
                        tuple(ESTADOS_ALFOMBRA[1]): {4, 5, 6, 13, 14, 15},
                        tuple(ESTADOS_ALFOMBRA[2]): {7, 8, 9, 16, 17, 18}
                    }.get(tuple(estado_siguiente), set())

                    # Verificar si hay al menos un asiento disponible en ese estado
                    asiento_libre = any(
                        asiento.asiento.id in asientos_estado_siguiente and asiento.asiento.esta_libre()
                        for asiento in self.sprite_asientos
                    )

                    if not self.alfombra_ocupada[i+1] and asiento_libre:  
                        # Solo avanza si el estado siguiente está vacío y hay un asiento libre
                        persona.actualizar_destino([estado_siguiente])
                        self.alfombra_ocupada[i+1] = persona
                        self.alfombra_ocupada[i] = False  # Liberar la posición anterior'''
    
    def avanzar_alfombra(self):
        for i in range(len(self.alfombra_ocupada) - 1, -1, -1):
            persona = self.alfombra_ocupada[i]
            if not persona:
                continue

            if i < len(self.alfombra_ocupada) - 1 and not self.alfombra_ocupada[i + 1]:
                siguiente_estado = ESTADOS_ALFOMBRA[i + 1]
                if siguiente_estado == persona.destino_fila:
                    # Se mueve a su estado fila (intermedio)
                    self.alfombra_ocupada[i + 1] = persona
                    self.alfombra_ocupada[i] = False
                    persona.actualizar_destino([siguiente_estado])
                elif siguiente_estado != persona.destino_fila:
                    # Aún puede avanzar en la alfombra si no ha llegado a destino fila
                    self.alfombra_ocupada[i + 1] = persona
                    self.alfombra_ocupada[i] = False
                    persona.actualizar_destino([siguiente_estado])
            elif i == len(self.alfombra_ocupada) - 1 and persona.destino_fila == ESTADOS_ALFOMBRA[i]:
                # Ya llegó a su estado fila, ahora va al asiento
                if persona.asiento_asignado.esta_libre():
                    persona.asiento_asignado.ocupar()
                    persona.actualizar_destino([persona.destino_final])
                    self.alfombra_ocupada[i] = False

    def generarAsientos(self):
        asientos_modelo = [Asiento(i + 1) for i in range(18)]
        for i, pos in enumerate(POSICION_IMG_ASIENTOS):
            asien_model = asientos_modelo[i]
            asien_model.coordenadas_atencion = pos
            sprite = SpriteAsiento(asien_model, pygame.Rect(pos[0], pos[1], 120, 115))
            self.sprite_asientos.append(sprite)
        self.vista.dibujar(self.sprite_asientos)
