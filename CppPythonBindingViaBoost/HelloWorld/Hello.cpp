#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

#include <boost/python/class.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_value_policy.hpp>

class Bar
{
 public:
   Bar(int x) : x(x) {}
   int get_x() const { return x; }
   void set_x(int x) { this->x = x; }
 private:
   int x;
};

class Foo
{
 public:
   Foo(int x) : b(x) {}

   // Returns an internal reference
   Bar const& get_bar() const { return b; }

 private:
   Bar b;
};

using namespace boost::python;
BOOST_PYTHON_MODULE(hello)
{
    class_<Bar>("Bar", init<int>())
        .def("get_x", &Bar::get_x)
        .def("set_x", &Bar::set_x)
        ;

    class_<Foo>("Foo", init<int>())
        .def("get_bar", &Foo::get_bar
          , return_internal_reference<>())
      ;
        
}
