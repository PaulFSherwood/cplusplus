#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <vector>

class Array {
	public:
		// Speical Memeber functions
		// (1) Constructor
		Array();
		// (2) Destructor
		~Array();
		// (3) Copy Constructor
		Array(const Array& rhs);
		// (3 or 4) Copy Assignment operator
		Array& operator=(const Array& rhs);
		
		void PrintingData();
		void SetData(int index, int value);

	private:
		std::vector<int> data;
};

#endif
