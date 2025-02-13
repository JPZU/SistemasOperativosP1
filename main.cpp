#include "ManejadorArchivo.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada> [archivo_salida]" << std::endl;
        return 1;
    }

    std::string archivoEntrada = argv[1];
    std::string archivoSalida = (argc > 2) ? argv[2] : "salida.bin";

    ManejadorArchivo manejador;

    if (manejador.leerArchivo(archivoEntrada)) {
        manejador.convertirABits(3);  // Cifrado César con desplazamiento +3 en ASCII
        manejador.mostrarBits();
        manejador.escribirArchivo(archivoSalida);
    }

    return 0;
}
