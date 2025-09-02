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
        #self.personas_en_ventanilla = pygame.sprite.Group()
        self.personas_en_ventanilla =  {}
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

    def entraNuevaPersona(self, tiempo_ultimo_generado):
        posicion_inicial = tuple(ESTADOS_FILA[0]) 
        espacio_libre = not any(sprite.rect.collidepoint(posicion_inicial) for sprite in self.personas_en_cola)

        if espacio_libre and tiempo_ultimo_generado >= self.tiempo_siguiente_llegada:
            nueva = self.generar_persona()
            nueva.actualizar_destino([tuple(dest) for dest in ESTADOS_FILA])  # Asegurar tuplas
            self.tiempo_siguiente_llegada = tiempo_ultimo_generado + random.randint(TIEMPO_MIN, TIEMPO_MAX)

  
    def avanzarFila(self):
        for i in range(len(ESTADOS_FILA) - 1):  # Iterar por la fila excepto la última posición
            posicion_actual = ESTADOS_FILA[i]
            posicion_siguiente = ESTADOS_FILA[i + 1]

            # Verificar si hay una persona en la posición actual
            persona_actual = next((p for p in self.personas_en_cola if tuple(p.rect.topleft) == tuple(posicion_actual)), None)

            # Verificar si la siguiente posición está libre
            espacio_libre = not any(p.rect.collidepoint(posicion_siguiente) for p in self.personas_en_cola)

            # Mover a la persona si hay espacio disponible
            if persona_actual and espacio_libre:
                persona_actual.actualizar_destino([posicion_siguiente])

    def finalizarAtencion(self, tiempo_ultimo_generado): #finaliza la atencion y sale del banco
        terminadas = []
        for persona, (sprite, ventanilla, tiempo_fin) in self.personas_en_ventanilla.items():
            if tiempo_ultimo_generado >= tiempo_fin and sprite.llego_al_destino():
                if (sprite.pos_x == 115 or sprite.pos_x == 140): sprite.actualizar_destino([POSICION_SALIDA[0]])
                else: sprite.actualizar_destino([POSICION_SALIDA[1]]) 
                sprite.en_ventanilla = False
                ventanilla.liberar()
                terminadas.append(persona)

        for persona in terminadas:
            del self.personas_en_ventanilla[persona]

    def eliminarPersona(self): # 4. Eliminar personas que llegaron a la salida
        eliminados = []
        for sprite in self.personas_en_cola:
            if not sprite.en_ventanilla and sprite.llego_al_destino() and tuple(sprite.destino_actual or []) == tuple(POSICION_SALIDA):
                eliminados.append(sprite)

        for sprite in eliminados:
            self.personas_en_cola.remove(sprite)

    def update(self):
        tiempo_ultimo_generado = pygame.time.get_ticks() 
        intervalo_generacion = random.randint(TIEMPO_MIN, TIEMPO_MAX)  

        self.entraNuevaPersona(tiempo_ultimo_generado)
        self.avanzarFila()
        
        for sprite in self.personas_en_cola:
            if not sprite.en_ventanilla and sprite.llego_al_destino():
                persona = sprite.persona
                for ventanilla in self.fila_banco.ventanillas:
                    if ventanilla.esta_libre():
                        asignada = self.fila_banco.asignar_ventanilla(ventanilla)
                        if asignada == persona:
                            pos_index = ventanilla.id - 1
                            sprite.actualizar_destino([POSICION_VENTANILLAS[pos_index]])
                            sprite.en_ventanilla = True
                            tiempo_fin = tiempo_ultimo_generado + random.randint(10000, 15000)  # 10–15 seg
                            self.personas_en_ventanilla[persona] = (sprite, ventanilla, tiempo_fin)
                        break  # Ya se le asignó una ventanilla, salir del loop

        self.finalizarAtencion(tiempo_ultimo_generado)
        self.eliminarPersona()

        # 5. Actualizar todos los sprites y redibujar
        self.personas_en_cola.update()
        self.vista.dibujar([self.sprite_ventanillas, self.personas_en_cola])

    def buscar_sprite_por_persona(self, persona):
        for sprite in self.personas_en_cola:
            if sprite.persona == persona:
                return sprite
        return None
    
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
            sprite = SpriteVentanilla(vent_model, pygame.Rect(pos[0], pos[1], 120, 115))
            self.sprite_ventanillas.append(sprite)
        self.vista.dibujar(self.sprite_ventanillas)