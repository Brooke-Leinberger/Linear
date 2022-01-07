typedef struct vector 
{
	int count;
	double* elements;
} vector;

vector* create_vector(int count, double* elements, vector* dest);
int free_vector(struct vector* vec);
vector* clone_vector(vector* vec, vector* dest);
vector* scale_vector(double scale, vector* vec, vector* dest);
double magnitude_vector(vector* vec);
vector* normalize_vector(vector* vec, vector* dest);
double dot_product(vector* left, vector* right);
vector* cross_product(vector* left, vector* right, vector* dest);
