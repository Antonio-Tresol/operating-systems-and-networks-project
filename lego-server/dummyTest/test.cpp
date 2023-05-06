#include "/home/redes/Documents/pi-redes-sistemas-operativos/lego-server/main/include/data/FigureHtmlRepository.hpp"
#include <iostream>
int main() {
	FigureHtmlRepository* rep = new FigureHtmlRepository;
	std::cout << rep->findByName("unicorn") << std::endl;
	delete rep;
}
