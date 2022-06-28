#pragma once
#ifdef JUEGO_EXPORTS
#define JUEGO_API __declspec(dllexport)
#else
#define JUEGO_API __declspec(dllimport)
#endif

/// <summary>
/// Aquí se registran los componentes únicos de cada juego que por tanto no conoce el motor
/// </summary>
void RegistryGameComponents();

/// <summary>
/// Carga la musica de fondo del juego
/// </summary>
void loadMusic();

/// <summary>
/// FUNCIÓN PRINCIPAL PARA CARGAR EL JUEGO, LOS JUEGOS NECESITARÁN ESTA FUNCION OBLIGATORIAMENTE PARA QUE EL MOTOR PUEDA LLAMAR A LA LIBRERÍA DINÁMICA
/// </summary>
extern "C" JUEGO_API int LoadGame();


