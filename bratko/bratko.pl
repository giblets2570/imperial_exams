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

