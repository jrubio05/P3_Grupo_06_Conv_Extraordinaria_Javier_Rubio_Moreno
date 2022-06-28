local level = {
    backgroundColor="0.79,0.52,1.0",
    ambient="1.0,1.0,1.0",
    gravity="0.0,0.0,0.0",
    camera = {
        nearClipDistance="1",
        farClipDistance="10000",
        camPosition="0,2500,0",
        camRotation="0.0,0.0,0.0"
    },
    entidades = {
        {
            name="Player",
            id=0,
            components={
                transform={
                    parent="-1",
                    position="0,0,0",
                    rotation="0,0,0",
                    scale="1.0,1.0,1.0"
                },
                mesh={
                    mesh="ninja.mesh",
                    material="",
                    visible="true"
                },
                collider={
                    type="box",
                    x="50.0",
                    y="50.0",
                    z="50.0",
                    trigger="false"
                },
                rigidbody={
                    position="0,0,0",
                    static="false",
                    density="1000"
                },
                personaje={
                    maxHealth="3",
                    lifefactor="0.05"
                },
                jugador={
                    speed="500"
                },
                lookatMouse={
                    test="false"
                },
				shoot={
					shootTime="500"
				}
            }
        },
        {
            name="SpanwZombies",
            id=0,
            components={
                transform={
                    parent="-1",
                    position="0,0,0",
                    rotation="0,0,0",
                    scale="1,1,1"
                },
                spawnZombis={
                    null="",
                }
            }
        }
    }
}

function GetLevel ()
  return level
end

function pruebaTexto()
    print('Im Working YESS')
end

