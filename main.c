#include "log.h"

int main()
{
    log_set(1);
	log_info("Hello there!");
	log_info("Age: %d", 24);
	log_info("Age %s");
	log_info("Hello world! My name is [%s], I am %d years old and my first initial is %c", "Santi", 24, 'S');
	return 0;
}
