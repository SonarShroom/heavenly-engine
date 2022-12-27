// Needed to compile glm without warnings
// Clang also defines GNUC, as it doesnt specifically mean GCC/G++
// source: (https://stackoverflow.com/questions/38499462/how-to-tell-clang-to-stop-pretending-to-be-other-compilers)
#if defined(__GNUC__) && !defined(__clang__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvolatile"
#elif defined(__clang__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if defined(__GNUC__) && !defined(__clang__)
	#pragma GCC diagnostic pop
#elif defined(__clang__)
	#pragma clang diagnostic pop
#endif