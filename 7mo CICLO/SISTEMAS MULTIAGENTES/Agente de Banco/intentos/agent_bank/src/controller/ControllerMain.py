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
        self.vista = View(1300,700)
        self.personas_en_cola = pygame.sprite.Group()
        self.personas_en_ventanilla = pygame.sprite.Group()
        self.personas_saliendo = pygame.sprite.Group()
        self.sprite_ventanillas = []
        self.generarVentanillas()
        # Tiempos
        self.tiempo_siguiente_llegada = pygame.time.get_ticks() + random.randint(100, 150)

    def ejecutar (self):
        reloj = pygame.time.Clock()

        done = False
        while not done:
            for event in pygame.event.get():
                if event.type == pygame.QUIT: done = True
                if event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = event.pos
                    print(f"Click en: ({x}, {y})")
                
            self.update()
            reloj.tick(FPS) 

    def update(self):
        tiempo_ultimo_generado = pygame.time.get_ticks() 
        intervalo_generacion = random.randint(TIEMPO_MIN, TIEMPO_MAX)  
        #print("entra a update")
        #for i, j in enumerate(self.personas_en_cola):
            #print(f"Persona {i} {j.index_cola}")
        self.entraNuevaPersona(tiempo_ultimo_generado)
        self.avanzarFila()
        self.avanzarVentanilla()

        # Actualizar todos los sprites y redibujar
        self.personas_en_cola.update()
        self.vista.dibujar([self.sprite_ventanillas, self.personas_en_cola, self.personas_en_ventanilla, self.personas_saliendo])

    def entraNuevaPersona(self, tiempo_ultimo_generado):
        if not self.buscarPersonaPosicion(self.personas_en_cola, ESTADOS_FILA[0]) and tiempo_ultimo_generado >= self.tiempo_siguiente_llegada:
            print("generando nueva persona")
            nueva = self.generar_persona()
            nueva.update_destino(ESTADOS_FILA[0]) 
            self.tiempo_siguiente_llegada = tiempo_ultimo_generado + random.randint(TIEMPO_MIN, TIEMPO_MAX)
            if nueva.persona.es_prioritaria():
                self.vista.presentarPantalla("Ingresando persona prioritaria\nCeder el turno")

    def buscarPersonaPosicion(self, personas, posicion):
        posicion = tuple(posicion)
        umbral = 5  # tolerancia en píxeles
        for persona in personas:
            pos_actual = persona.rect.topleft
            if abs(pos_actual[0] - posicion[0]) <= umbral and abs(pos_actual[1] - posicion[1]) <= umbral:
                #print(f"Si existe persona en {posicion}")
                return persona
        return None
    
    def avanzarVentanilla(self):
        for persona in self.personas_en_cola:
            if persona.index_cola == len(ESTADOS_FILA) - 1: 
                for ventanilla in self.sprite_ventanillas:
                    if ventanilla.ventanilla.esta_libre: 
                        print(f"La persona {persona.tipo_imagen} pasa a la ventanilla {ventanilla.coordenadas_atencion}")
                        ventanilla.ventanilla.atender(persona)
                        persona.update_destino(ventanilla.coordenadas_atencion)
                        
                        # Marcar ventanilla como ocupada
                        ventanilla.ventanilla.esta_libre = False

                        # Remover la persona de la cola y agregarla a ventanillas
                        self.personas_en_cola.remove(persona)
                        self.personas_en_ventanilla.add(persona)
                        
                        break

        

    def avanzarFila(self):
        for persona in self.personas_en_cola:
            puesto_actual = tuple(ESTADOS_FILA[persona.index_cola])
            if abs(persona.rect.topleft[0] - puesto_actual[0]) <= 5 and abs(persona.rect.topleft[1] - puesto_actual[1]) <= 5:
                if persona.index_cola < len(ESTADOS_FILA) - 1:
                    puesto_siguiente = tuple(ESTADOS_FILA[persona.index_cola + 1])
                    if not self.buscarPersonaPosicion(self.personas_en_cola, puesto_siguiente):
                        persona.index_cola += 1
                        persona.update_destino(puesto_siguiente)


    def generar_persona(self):
        tipos = ['discapacitado', 'embarazada', 'madre', 'hombre_normal', 'mujer_normal', 'mujer_terceraEdad', 'hombre_terceraEdad']
        pesos = [1, 1, 1, 3, 3, 1, 1]
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
         # Crear modelos de ventanillas
        ventanillas_modelo = [Ventanilla(i + 1) for i in range(4)]
        self.fila_banco = FilaBanco(ventanillas_modelo)

        for i, pos in enumerate(POSICION_IMG_VENTANILLAS):
            vent_model = ventanillas_modelo[i]
            sprite = SpriteVentanilla(vent_model, POSICION_VENTANILLAS[i],pygame.Rect(pos[0], pos[1], 120, 115))
            self.sprite_ventanillas.append(sprite)
        self.vista.dibujar(self.sprite_ventanillas)