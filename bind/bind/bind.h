//
//  bind.h
//  bind
//
//  Created by Vadim on 21/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef bind_h
#define bind_h

template <int N>
struct placeholder
{};

constexpr placeholder<1> _1;
constexpr placeholder<2> _2;
constexpr placeholder<3> _3;
constexpr placeholder<4> _4;
constexpr placeholder<5> _5;
constexpr placeholder<6> _6;
constexpr placeholder<7> _7;
constexpr placeholder<8> _8;

template <typename A>
struct G {
    A a;

    G(A a)
    : a(a)
    {}
    
    template <typename ... B>
    A operator() (B...) const {
        return a;
    }
    
};

template <>
struct G<placeholder<1> >
{
    G(placeholder<1>)
    {}
    
    template <typename B1, typename ... Bs>
    B1 operator()(B1 b1, Bs ...) const
    {
        return b1;
    }
};

template <int N>
struct G<placeholder<N>> {
    G(placeholder<N>)
    {}
    
    template <typename B1, typename... Bs>
    decltype(auto) operator()(B1 b1, Bs... rest) const {
        return G<placeholder<N - 1>>((placeholder<N - 1>()))(rest...);
    }
    
};

template <typename F, typename... As>
class bind_t {
    
    F f;
    std::tuple<G<As>...> gs;
    
    template <int... ks, typename ... Bs>
    decltype(auto) call(std::integer_sequence<int, ks...>, Bs ... bs) const {
        return f(std::get<ks>(gs)(bs...)...);
    }
    
public:
    
    bind_t(F f, As... as)
    : f(f), gs(as...)
    {}
    
    template <typename ... Bs>
    decltype(auto) operator()(Bs ... bs) const {
        return call(std::make_integer_sequence<int, sizeof...(As)>(), bs...);
    }
    
};

template <typename F, typename ... As>
struct G<bind_t<F, As...> > {
    
    G(bind_t<F, As...> bnd)
    : bnd(bnd)
    {}
    
    template <typename... Bs>
    decltype(auto) operator()(Bs... arguments) const {
        return bnd(arguments...);
    }
    
    bind_t<F, As...> bnd;
};

template <typename F, typename ... As>
bind_t<F, As...> bind(F f, As ... as) {
    return bind_t<F, As...>(f, as...);
}


#endif /* bind_h */
