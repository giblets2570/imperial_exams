%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.11 flatten
%
%%%%%%%%%%%%%%%%%%%%%%%

flatten(L,X) :-
    flatten(L,[],X),!.

flatten([],X,X).

flatten([[H|T]|T2],Acc,X):-
    append(T,T2,T3),
    flatten([H|T3],Acc,X).

flatten([[]|T],Acc,X):-
    flatten(T,Acc,X).

flatten([H|T],Acc,X):-
    append(Acc,[H],NAcc),
    flatten(T,NAcc,X).

%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                                                                                                                         
%    5.1 cut                                                                                                                                     
%                                                                                                                                                                    
%%%%%%%%%%%%%%%%%%%%%%%

p(1).
p(2) :- !.
p(3).

%%%%%%%%%%%%%%%%%%%%%%%
%
%    2.3 triangles
%
%%%%%%%%%%%%%%%%%%%%%%%

point(X,Y).

triangle(point(-1,0),point(1,0),point(0,Y)).

%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.3 listLength
%
%%%%%%%%%%%%%%%%%%%%%%%

evenlength(L):-
    evenlength(L,0).

evenlength([],0).

evenlength([H|T],N) :-
    NN is mod(N+1,2),
    evenlength(T,NN).

%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.4 reverse
%
%%%%%%%%%%%%%%%%%%%%%%%

reverse(L,X) :-
    reverse(L,[],X).

reverse([],X,X).

reverse([H|T],Acc,X):-
    reverse(T,[H|Acc],X).

reverse2([],[]).

reverse2([H|T],NX):-
    reverse2(T,X),
    append(X,[H],NX).

%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.5 palindrome
%
%%%%%%%%%%%%%%%%%%%%%%%

equal([],[]).

equal([H|T1],[H|T2]) :-
    equal(T1,T2).

palindrome(List) :-
    reverse(List,Rlist),
    equal(List,Rlist).

%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.6 shift
%
%%%%%%%%%%%%%%%%%%%%%%%

shift([H|T],List) :-
    shift(T,List,[],H).

shift([],X,Acc,H) :-
    append(Acc,[H],X).

shift([Head|Tail],X,Acc,H) :-
    append(Acc,[Head],Nacc),
    shift(Tail,X,Nacc,H).

%%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.8 subset
%
%%%%%%%%%%%%%%%%%%%%%%%%

subset(List,List).

subset([H|T1],[H|T2]) :-
    subset(T1,T2).

subset([_|T1],T2) :-
    subset(T1,T2).

%%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.18 sumlist
%
%%%%%%%%%%%%%%%%%%%%%%%%

sumlist([H],H).

sumlist([H1,H2|T],X):-
    H is H1 + H2,
    sumlist([H|T],X).


%%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.19 ordered
%
%%%%%%%%%%%%%%%%%%%%%%%%

ordered([_]).

ordered([H1,H2|T]) :-
    H1 =< H2,
    ordered([H2|T]).

%%%%%%%%%%%%%%%%%%%%%%%%
%
%    3.21 between
%
%%%%%%%%%%%%%%%%%%%%%%%%

between(N1,N2,X) :-
    N1 =< N2,
    X = N1.

between(N1,N2,X) :-
    NN1 is N1 + 1,
    NN1 =< N2,
    between(NN1,N2,X).

%%%%%%%%%%%%%%%%%%%%%%%%
%
%    
%
%%%%%%%%%%%%%%%%%%%%%%%%
