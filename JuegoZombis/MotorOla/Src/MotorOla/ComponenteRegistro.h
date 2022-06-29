#pragma once

#include "ComponenteFactoria.h"
#include "ECS.h"
#include "utils/Singleton.h"

// Registro de los nuevos componentes
// Ejemplo: ComponenteRegistro::ComponenteRegistro<Transform>("transform");
namespace ComponenteRegistro {
	template<typename T> class ComponenteRegistro {
	public:
		ComponenteRegistro(std::string compName) {
			// CUIDADO QUE EL ComponenteFactoria ES SINGLETON Y DEBE EXISTIR A ESTAS ALTURAS
			ComponenteFactoria::instance()->registerGenerator(compName, []()
				{
					return static_cast<Componente*>(new T());
				}
			);
		}
	};
}