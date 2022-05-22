
using namespace boost::python;

BOOST_PYTHON_MODULE(classes)
        {
                class_<World>("World")
                        .def("greet", &World::greet)
                        .def("set", &World::set)
                ;
        };