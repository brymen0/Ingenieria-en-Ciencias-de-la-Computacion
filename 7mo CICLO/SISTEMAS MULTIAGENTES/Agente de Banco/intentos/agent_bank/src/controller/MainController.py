import pygame
import random
from view.View import View
from view.SpriteVentanilla import SpriteVentanilla
from view.SpritePersona import SpritePersona
from model.Ventanilla import Ventanilla
from model.Persona import Persona
from model.constantes import ESTADOS_FILA, POSICION_VENTANILLAS, FPS, DARK_GRAY

class MainController():
    def __init__(self):
        pygame.init()
        self.vista = View(1300,700)
        self.personas_en_cola = pygame.sprite.Group()
        self.todas_personas = pygame.sprite.Group()
        self.ventanillas = []

    def ejecutar (self):
        reloj = pygame.time.Clock()
        self.crearVentanillas()

        tiempo_ultimo_generado = pygame.time.get_ticks() 
        intervalo_generacion = random.randint(5000, 9000)  # Generar cada 4-7 segundos aleatorios

        done = False
        while not done:
            for event in pygame.event.get():
                if event.type == pygame.QUIT: done = True
                if event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = event.pos
                    print(f"Click en: ({x}, {y})")
                    for persona in self.personas_en_cola:
                        if persona.index + 1 < len(ESTADOS_FILA):  # Evitar desbordamiento de índice
                            persona.mover(*ESTADOS_FILA[persona.index + 1])
                            persona.index += 1  # Avanzar en la fila
            
            self.entraPersona(tiempo_ultimo_generado, intervalo_generacion)
            self.avanzarVentanilla()

            # simular movimiento de la persona
            for persona in self.personas_en_cola:
                persona.actualizar()

            self.vista.pantalla.fill(DARK_GRAY)
            self.vista.init_view()
            self.vista.dibujar(self.ventanillas)
            self.todas_personas.draw(self.vista.pantalla)

            pygame.display.flip()
            reloj.tick(FPS) 

    def avanzarVentanilla(self):
        for persona in self.personas_en_cola:
            if persona.rect.topleft == ESTADOS_FILA[-1]:  # Está al final de la fila
                for ventanilla in self.ventanillas:
                    if ventanilla.ventanilla.estado == "libre":
                        # Marcar ventanilla como ocupada
                        ventanilla.ventanilla.estado = "ocupada"
                        # Mover persona a la ventanilla
                        persona.mover(*ventanilla.rect.topleft)
                        # Sacar de la fila
                        self.personas_en_cola.remove(persona)
                        # (opcional) mantener en todas_personas si la sigues mostrando
                        return  # Salir luego de mover uno


    def proxima_persona_atender(self):
        ultima_posicion = ESTADOS_FILA[-1]  
        for persona in self.personas_en_cola:
            if persona.rect.topleft == ultima_posicion:
                return persona  
        return None 

    def entraPersona(self, tiempo_ultimo_generado, intervalo_generacion):
            tiempo_actual = pygame.time.get_ticks()
            if tiempo_actual - tiempo_ultimo_generado > intervalo_generacion:
                if not any(p.rect.collidepoint(ESTADOS_FILA[0]) for p in self.personas_en_cola):  #si espacio libre
                    nueva_persona = self.generarPersona()
                    self.personas_en_cola.add(nueva_persona)
                    self.todas_personas.add(nueva_persona)
                    tiempo_ultimo_generado = tiempo_actual  # Resetear temporizador
                    intervalo_generacion = random.randint(5000, 9000)  # Nuevo tiempo aleatorio

    def generarPersona(self):
        tipos = ['discapacitado','embarazada','madre','hombre_normal','mujer_normal','mujer_terceraEdad','hombre_terceraEdad']
        pesos = [1, 1, 1, 3, 3, 1, 1]  # mayor peso para hombre_normal y mujer_normal
        tipo_persona = random.choices(tipos, weights=pesos, k=1)[0]

        persona = None
        match tipo_persona:
            case 'discapacitado':
                persona = SpritePersona(Persona(random.randint(18,100), False, False, True), 'discapacitado')
            case 'embarazada':
                persona = SpritePersona(Persona(random.randint(18,100), True, False, False), 'embarazada')
            case 'madre':
                persona = SpritePersona(Persona(random.randint(18,100), False, True, False), 'madre')
            case 'hombre_normal':
                persona = SpritePersona(Persona(random.randint(18,100), False, False, False), 'hombre_normal')
            case 'mujer_normal':
                persona = SpritePersona(Persona(random.randint(18,100), False, False, False), 'mujer_normal')
            case 'mujer_terceraEdad':
                persona = SpritePersona(Persona(random.randint(65,100), False, False, False), 'mujer_terceraEdad')
            case 'hombre_terceraEdad':
                persona = SpritePersona(Persona(random.randint(65,100), False, False, False), 'hombre_terceraEdad')
        return persona


    def crearVentanillas(self):
        '''return [Ventanilla(1),
                Ventanilla(2),
                Ventanilla(3),
                Ventanilla(4)]'''
        self.ventanillas = [SpriteVentanilla(Ventanilla(1),(95,110)),
                            SpriteVentanilla(Ventanilla(2),(385,110)),
                            SpriteVentanilla(Ventanilla(3),(800,110)),
                            SpriteVentanilla(Ventanilla(4),(1090,110))]
        #self.vista.dibujar(ventanillas)