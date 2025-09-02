import pygame
import random
from view.SpriteVentanilla import SpriteVentanilla
from view.SpritePersona import SpritePersona
from view.View import View
from model.Ventanilla import Ventanilla
from model.Persona import Persona
from model.FilaBanco import FilaBanco
from model.constantes import ESTADOS_FILA, POSICION_SALIDA, POSICION_VENTANILLAS, POSICION_IMG_VENTANILLAS, TIEMPO_MIN, TIEMPO_MAX, FPS

class MainController:
    def __init__(self):
        pygame.init()
        self.vista = View(1300, 700)
        self.personas_en_cola = pygame.sprite.Group()
        self.personas_ventanilla = pygame.sprite.Group()
        # Diccionario que mapea {persona: (sprite, ventanilla, tiempo_fin)}
        self.personas_en_ventanilla = {}
        self.personas_saliendo = pygame.sprite.Group()
        self.sprite_ventanillas = []
        self.generarVentanillas()
        # Programamos la llegada de la siguiente persona
        self.tiempo_siguiente_llegada = pygame.time.get_ticks() + random.randint(100, 150)

    def ejecutar(self):
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

    def entraNuevaPersona(self, tiempo_ultimo_generado):
        # Solo se genera una persona si la posición inicial de la fila está libre
        if not self.buscarPersonaPosicion(self.personas_en_cola, ESTADOS_FILA[0]) and tiempo_ultimo_generado >= self.tiempo_siguiente_llegada:
            #print("generando nueva persona")
            nueva = self.generar_persona()
            # Se asigna únicamente la primera posición de la fila
            nueva.actualizar_destino([ESTADOS_FILA[0]])
            self.tiempo_siguiente_llegada = tiempo_ultimo_generado + random.randint(TIEMPO_MIN, TIEMPO_MAX)
            if nueva.persona.es_prioritaria():
                self.vista.presentarPantalla("Ingresando persona\nprioritaria\nCeder el turno")

    def buscarPersonaPosicion(self, personas, posicion):
        posicion = tuple(posicion)
        umbral = 5   # tolerancia en píxeles
        for persona in personas:
            pos_actual = persona.rect.topleft
            if abs(pos_actual[0] - posicion[0]) <= umbral and abs(pos_actual[1] - posicion[1]) <= umbral:
                return persona
        return None

    def avanzarFila(self):
        # Recorre cada persona en la cola y, si llegó a su posición actual y no es la última,
        # le asigna el siguiente punto de la ruta (si está libre)
        for sprite in self.personas_en_cola:
            if sprite.llego_al_destino():
                if sprite.index_cola < len(ESTADOS_FILA) - 1:
                    siguiente_pos = ESTADOS_FILA[sprite.index_cola + 1]
                    if not self.buscarPersonaPosicion(self.personas_en_cola, siguiente_pos):
                        sprite.index_cola += 1
                        sprite.actualizar_destino([siguiente_pos])

    def finalizarAtencion(self, tiempo_ultimo_generado):
        """
        Cuando se cumple el tiempo asignado en ventanilla y la persona llegó a su destino,
        se le asigna el destino de salida correspondiente. Además, se libera la ventanilla.
        """
        terminadas = []
        for persona, (sprite, ventanilla, tiempo_fin) in self.personas_en_ventanilla.items():
            if tiempo_ultimo_generado >= tiempo_fin and sprite.llego_al_destino():
                # Verificamos la ubicación de la ventanilla atendida.
                if ventanilla.coordenadas_atencion == [95, 110] or ventanilla.coordenadas_atencion == [385, 110]:
                    salida = POSICION_SALIDA[0]  # Salida izquierda
                elif ventanilla.coordenadas_atencion == [800, 110] or ventanilla.coordenadas_atencion == [1090, 110]:
                    salida = POSICION_SALIDA[1]  # Salida derecha
                else:
                    salida = random.choice(POSICION_SALIDA)
                sprite.actualizar_destino([salida])
                sprite.en_ventanilla = False
                sprite.atendido = True
                ventanilla.liberar()
                terminadas.append(persona)
        for persona in terminadas:
            del self.personas_en_ventanilla[persona]

    def eliminarPersona(self):
        # Elimina los sprites que ya se dirigieron a la salida y han finalizado su movimiento
        eliminados = []
        for sprite in self.personas_ventanilla:
            if not sprite.en_ventanilla and sprite.llego_al_destino() and sprite.fue_atendido():
                eliminados.append(sprite)
        for sprite in eliminados:
            self.personas_ventanilla.remove(sprite)

    def update(self):
        tiempo_ultimo_generado = pygame.time.get_ticks()
        self.entraNuevaPersona(tiempo_ultimo_generado)
        self.avanzarFila()
        # Asignación a ventanilla cuando la persona se encuentra en la última posición de la fila
        for sprite in list(self.personas_en_cola):
            if not sprite.en_ventanilla and sprite.llego_al_destino() and sprite.index_cola == len(ESTADOS_FILA) - 1:
                persona = sprite.persona
                for ventanilla in self.fila_banco.ventanillas:
                    if ventanilla.esta_libre():
                        asignada = self.fila_banco.asignar_ventanilla(ventanilla)
                        self.personas_ventanilla.add(sprite)
                        self.personas_en_cola.remove(sprite)
                        if asignada == persona:
                            pos_index = ventanilla.id - 1
                            # Mueve la persona hacia la posición de la ventanilla asignada
                            sprite.actualizar_destino([POSICION_VENTANILLAS[pos_index]])
                            sprite.en_ventanilla = True
                            # Se asigna un tiempo de atención extendido (15 a 20 segundos)
                            tiempo_fin = tiempo_ultimo_generado + random.randint(20000, 25000)
                            self.personas_en_ventanilla[persona] = (sprite, ventanilla, tiempo_fin)
                            self.vista.presentarPantalla(f"Siguiente persona\nVentanilla {ventanilla.id}")

                        break

        self.finalizarAtencion(tiempo_ultimo_generado)
        self.eliminarPersona()
        self.personas_en_cola.update()
        self.personas_ventanilla.update()
        self.vista.dibujar([self.sprite_ventanillas, self.personas_en_cola, self.personas_ventanilla])

    def generar_persona(self):
        tipos = ['discapacitado', 'embarazada', 'madre', 'hombre_normal', 'mujer_normal', 'mujer_terceraEdad', 'hombre_terceraEdad']
        pesos = [1, 2, 2, 7, 7, 3, 3]
        tipo = random.choices(tipos, weights=pesos, k=1)[0]
        persona = None
        match tipo:
            case 'discapacitado':
                persona = Persona(random.randint(18, 100), False, False, True)
            case 'embarazada':
                persona = Persona(random.randint(18, 100), True, False, False)
            case 'madre':
                persona = Persona(random.randint(18, 100), False, True, False)
            case 'hombre_normal':
                persona = Persona(random.randint(18, 64), False, False, False)
            case 'mujer_normal':
                persona = Persona(random.randint(18, 64), False, False, False)
            case 'mujer_terceraEdad':
                persona = Persona(random.randint(65, 100), False, False, False)
            case 'hombre_terceraEdad':
                persona = Persona(random.randint(65, 100), False, False, False)
        sprite = SpritePersona(persona, tipo)
        self.personas_en_cola.add(sprite)
        self.fila_banco.agregar_persona(persona)
        return sprite

    def generarVentanillas(self):
        # Se crean los modelos para 4 ventanillas
        ventanillas_modelo = [Ventanilla(i + 1) for i in range(4)]
        self.fila_banco = FilaBanco(ventanillas_modelo)
        for i, pos in enumerate(POSICION_IMG_VENTANILLAS):
            vent_model = ventanillas_modelo[i]
            # Asignamos al modelo la coordenada de atención,
            # por ejemplo, para ventanillas izquierdas: [95,110] o [385,110]
            # y para las derechas: [800,110] o [1090,110]
            vent_model.coordenadas_atencion = pos
            sprite = SpriteVentanilla(vent_model, pygame.Rect(pos[0], pos[1], 120, 115))
            self.sprite_ventanillas.append(sprite)
        self.vista.dibujar(self.sprite_ventanillas)
