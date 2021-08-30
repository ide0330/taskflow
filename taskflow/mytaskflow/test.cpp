#include "../taskflow.hpp"
 
int main(){
 
    tf::Taskflow tf;
 
    auto [A, B, C, D, E] = tf.emplace(
        [] () {},
        [] () {},
        [] () {},
        [] () {},
        [] () {}
    );
 
    A.precede(B, C, E);
    C.precede(D);
    B.precede(D, E);
 
    A.name("A");
    B.name("B");
    C.name("C");
    D.name("D");
    E.name("E");
 
    tf.dump(std::cout);
 
    return 0;
}