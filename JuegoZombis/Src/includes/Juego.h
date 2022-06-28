#pragma once
#ifdef JUEGO_EXPORTS
#define JUEGO_API __declspec(dllexport)
#else
#define JUEGO_API __declspec(dllimport)
#endif

/// <summary>
/// Aqu� se registran los componentes �nicos de cada juego que por tanto no conoce el motor
/// </summary>
void RegistryGameComponents();

/// <summary>
/// Carga la musica de fondo del juego
/// </summary>
void loadMusic();

/// <summary>
/// FUNCI�N PRINCIPAL PARA CARGAR EL JUEGO, LOS JUEGOS NECESITAR�N ESTA FUNCION OBLIGATORIAMENTE PARA QUE EL MOTOR PUEDA LLAMAR A LA LIBRER�A DIN�MICA
/// </summary>
extern "C" JUEGO_API int LoadGame();


