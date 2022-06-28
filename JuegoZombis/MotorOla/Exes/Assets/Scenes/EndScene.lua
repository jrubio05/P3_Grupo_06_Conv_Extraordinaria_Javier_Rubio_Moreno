local endScene = {
    backgroundColor="0.6,1.0,0.0",
    ambient="0.1,0.1,0.1",
    gravity="0 -9.8 0",
    botones={
		{
			positionX="0.75",
			positionY="0.65",
			texto="Menu",
			nombrePanel="BackMenuPanel",
			nombreTexto="BackMenuTexto",
			tamLetra="0.05",
			material="LapidaButton",
			dimensionX="0.25",
			dimensionY="0.35"	
		}
    },	
}

function GetEndScene ()
  return endScene
end

function pruebaTexto()
    print('Im Working YESS')
end

