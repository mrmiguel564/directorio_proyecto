#include <global.h>
#include <checkArgs.hpp>

uint8_t  g_letraObjetivo;
std::vector<uint8_t> v;

uint32_t contarTotal = 0;
void contarParcial(auto V,auto inicio, auto final, auto g_letraObjetivo) {
    	for(auto i= inicio; i<final;i++){
			if(V[i] == g_letraObjetivo){
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
	auto di=totalElementos/numThreads;

	std::thread t[numThreads] //(contarParcial, di*(i-1) , (di*i)-1, g_letraObjetivo);	
	

	for (int i = 0; i < numThreads; ++i){
		t[i] = std::thread(contarParcial,V ,di*(i-1) , (di*i)-1, g_letraObjetivo);
	}
	
	for (int i = 0; i < numThreads; ++i){
		t[i].join();
	}

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeThread = elapsed.count();
	
	std::cout << "Apariciones de '" << g_letraObjetivo << "': "<< contarTotal << std::endl;
	std::cout << "Tiempo de busqueda P/C: " << totalTimeThread << "[ms]" << std::endl;
	
	

	return(EXIT_SUCCESS);
}

