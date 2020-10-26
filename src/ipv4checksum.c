#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* Prototype for main function */
static PyObject* checksum(PyObject*, PyObject*);

/* List methods and module definition */
static PyMethodDef MyMethods[] = {
	{"checksum",  checksum, METH_VARARGS, "Compute an IPv4 checksum of arbitrary data."},
	{NULL, NULL, 0, NULL}	/* Sentinel */
};
static struct PyModuleDef mymodule = {
	.m_base = PyModuleDef_HEAD_INIT,
	.m_name = "ipv4checksum",
	.m_doc = NULL,
	.m_size = -1,
	.m_methods = MyMethods,
	.m_slots = NULL
};

PyMODINIT_FUNC PyInit_ipv4checksum() {
	return PyModule_Create(&mymodule);
}

/* Compute an IPv4 checksum */
static uint16_t _checksum(const void* data, int len) {
	uint32_t checksum = 0;
	unsigned int left = len;
	const uint16_t* ptr_16 = data;

	while (left > 1) {
		checksum += *ptr_16++;
		left -= 2;
	}

	if (left) {
		checksum += *(uint8_t*) ptr_16;
	}

	/* Fold result into 16 bits */
	while (checksum > 0xffff) {
		checksum = (checksum >> 16) + (checksum & 0xFFFF);
	}

	return (uint16_t) ~checksum;
}

/* Main function that wraps over `_checksum` */
static PyObject* checksum(PyObject* self, PyObject* arg) {
	const unsigned char* data;
	Py_ssize_t count;
	uint32_t result;

	(void)self;

	if (PyArg_ParseTuple(arg, "s#", &data, &count) == 0) {
		return NULL;
	}

	result = _checksum(data, count);
	return PyLong_FromLong((long) result);
}