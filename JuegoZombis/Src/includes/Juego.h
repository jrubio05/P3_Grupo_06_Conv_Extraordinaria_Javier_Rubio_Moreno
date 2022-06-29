#pragma once
#ifdef JUEGO_EXPORTS
#define JUEGO_API __declspec(dllexport)
#else
#define JUEGO_API __declspec(dllimport)
#endif

// Aqu� se registran los componentes �nicos de cada juego que por tanto no conoce el motor
void RegistryGameComponents();

// Carga la musica de fondo del juego
void loadMusic();

// FUNCI�N PRINCIPAL PARA CARGAR EL JUEGO
//LOS JUEGOS NECESITAR�N ESTA FUNCION OBLIGATORIAMENTE PARA QUE EL MOTOR PUEDA LLAMAR A LA LIBRER�A DIN�MICA
extern "C" JUEGO_API int LoadGame();
