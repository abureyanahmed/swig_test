%include "std_vector.i"
%include "std_set.i"
// Instantiate templates used by example
namespace std {
   %template(IntVector) vector<int>;
   %template(DoubleVector) vector<double>;
   %template(IntSet) set<int>;
   %template(SetIntVector) vector<set<int>>;
}

%module count_crossings_def
%{
extern std::vector<std::set<int> > count_crossings(int n, std::vector<double> x, std::vector<double> y, std::vector<int> edg_u, std::vector<int> edg_v);
%}

extern std::vector<std::set<int> > count_crossings(int n, std::vector<double> x, std::vector<double> y, std::vector<int> edg_u, std::vector<int> edg_v);

