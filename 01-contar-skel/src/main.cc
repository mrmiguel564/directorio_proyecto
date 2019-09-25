#include <global.h>
#include <checkArgs.hpp>

uint8_t  g_letraObjetivo;
std::vector<uint8_t> v;


void contarParcial(auto v, auto inicio, auto final, auto g_letraObjetivo) {
    	for(auto& tmpLetra : v){
		if(tmpLetra == g_letraObjetivo){
			contarTotal++;
		}
	}

}


int main(int argc, char** argv){
	
	uint32_t totalElementos;
	uint32_t numThreads;
	
    uint32_t contarSerial = 0;
	uint32_t contarTotal = 0;
	
	std::shared_ptr<checkArgs> argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	
	totalElementos = argumentos->getArgs().tamProblema;
	numThreads     = argumentos->getArgs().numThreads;
	g_letraObjetivo  = argumentos->getArgs().letra;
	
	std::cout << "Nro. Elementos: " << totalElementos << std::endl;
	std::cout << "Threads       : " << numThreads     << std::endl;
	std::cout << "Letra         : " << g_letraObjetivo  << std::endl;
	
	static thread_local std::random_device device;
	static thread_local std::mt19937 rng(device());
	
	std::cout << "Llenando arreglo ..." << std::endl;
	std::uniform_int_distribution<uint8_t> nRandom('a', 'z');
	for(size_t i=0; i < totalElementos; i++){
		uint8_t tmpLetra = nRandom(rng);
		v.push_back( tmpLetra ); 
		//std::cout << tmpLetra << std::endl;
	}
	std::cout << "... OK" << std::endl;
	
	//======SERIAL======
	auto start = std::chrono::high_resolution_clock::now();
	
	// Busca en forma serial
	for(auto& tmpLetra : v){
		if(tmpLetra == g_letraObjetivo){
			contarSerial++;
		}
	}
	
	//
	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeSerial = elapsed.count();
	
	std::cout << "Apariciones de '" << g_letraObjetivo << "': "<< contarSerial << std::endl;
	std::cout << "Tiempo de busqueda Secuencial: " << totalTimeSerial << "[ms]" << std::endl;

	
	//======THREADS======
	start = std::chrono::high_resolution_clock::now();
	//(1) Separación del trabajo
	// totalElementos 		numThreads   		 g_letraObjetivo
	auto di=totalElementos/numThreads; // 100 2    50    50 100 
		for(auto i=0;di*i>=totalElementos;i++){
			std::thread t1(contarParcial,v , inicio , final, g_letraObjetivo);
		}
	std::thread t1(contarParcial,v , inicio , final, g_letraObjetivo);
	t1.join();
	// Completar
	
	//(2) Reducción (Consolidación de resultados parciales)
	
	// Completar
	
	//
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeThread = elapsed.count();
	
	std::cout << "Apariciones de '" << g_letraObjetivo << "': "<< contarTotal << std::endl;
	std::cout << "Tiempo de busqueda P/C: " << totalTimeThread << "[ms]" << std::endl;
	
	

	return(EXIT_SUCCESS);
}

