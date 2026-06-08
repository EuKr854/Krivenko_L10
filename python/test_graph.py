from ctypes import *

graph_lib = CDLL("../libgraph.dll")

graph_lib.graph_init.argtypes = [c_void_p]
graph_lib.graph_init.restype = c_int

print("Library loaded successfully")
print("Function signatures configured")