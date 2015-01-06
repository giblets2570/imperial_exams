%%%%%%%%%%%%%%%%%%%%%%
%%   Question 1
%%%%%%%%%%%%%%%%%%%%%%

subList([],L).

subList([H|T],L):-
    member(H,L),
    sublist(T,L).
	
%%%%%%%%%%%%%%%%%%%%%%
%%   Question 2
%%%%%%%%%%%%%%%%%%%%%%

difference(L1,L2,L):-
	difference(L1,L2,[],L).

difference([],L2,L,L).

difference([H|T],L2,Acc,L):-
	member(H,L2),
	difference(T,L2,Acc,L).

difference([H|T],L2,Acc,L):-
	\+ member(H,L2),
	difference(T,L2,[H|Acc],L).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 3
%%%%%%%%%%%%%%%%%%%%%%

sift(L,N,Result):-
	sift(L,N,[],Result).

sift([],N,R,R).

sift([H|T],N,Acc,R):-
	H < N+1,
	sift(T,N,[H|Acc],R).

sift([H|T],N,Acc,R):-
	H > N,
	sift(T,N,Acc,R).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 4
%%%%%%%%%%%%%%%%%%%%%%

common(L1,L2,L):-
	common(L1,L2,[],L).

common([],L2,L,L).

common([H|T],L2,Acc,L):-
	\+ member(H,L2),
	common(T,L2,Acc,L).

common([H|T],L2,Acc,L):-
	member(H,L2),
	\+member(H,Acc),
	common(T,L2,[H|Acc],L).

common([H|T],L2,Acc,L):-
	member(H,L2),
	member(H,Acc),
	common(T,L2,Acc,L).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 5
%%%%%%%%%%%%%%%%%%%%%%

delete(L,Result):-
	delete(L,1,[],Result).

delete([],N,R,R).

delete([H|T],N,Acc,R):-
	0 is mod(N,2),
	delete(T,N+1,Acc,R).

delete([H|T],N,Acc,R):-
	1 is mod(N,2),
	delete(T,N+1,[H|Acc],R).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 6
%%%%%%%%%%%%%%%%%%%%%%

process(L1,[],[],[]).

process(L1,[(N,A,M)|T],NConsistent,Inconsistent) :-
	member((N,A),L1),
	process(L1,T,Consistent,Inconsistent),
	append([(N,A,M)],Consistent,NConsistent).

process(L1,[(N,A,M)|T],Consistent,NInconsistent) :-
	\+ member((N,A),L1),
	process(L1,T,Consistent,Inconsistent),
	append([(N,A,M)],Inconsistent,NInconsistent).


%%%%%%%%%%%%%%%%%%%%%%
%%   Question 7
%%%%%%%%%%%%%%%%%%%%%%

duplicate(L,X) :-
	duplicate(L,[],X).

duplicate([],X,X).

duplicate([H|T],Acc,X) :-
	append(Acc,[H,H],NAcc),
	duplicate(T,NAcc,X).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 8
%%%%%%%%%%%%%%%%%%%%%%

duplicateN(L,N,X) :-
	duplicateN(L,N,[],X).

duplicateN([],N,X,X).

duplicateN([H|T],N,Acc,X) :-
	makeNlist(H,N,L),
	append(Acc,L,NAcc),
	duplicateN(T,N,NAcc,X).

makeNlist(E,N,L) :-
	makeNlist(E,N,[E],L).

makeNlist(E,1,L,L).

makeNlist(E,N,Acc,L) :-
	Ln is N-1,
	makeNlist(E,Ln,[E|Acc],L),
	!.

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 9
%%%%%%%%%%%%%%%%%%%%%%

drop(L,N,X) :-
	drop(L,N,1,[],X).

drop([],N,_,X,X).

drop([H|T],N,Index,Acc,X) :-
	0 is mod(Index,N),
	drop(T,N,Index+1,Acc,X).

drop([H|T],N,Index,Acc,X) :-
	\+ (0 is mod(Index,N)),
	drop(T,N,Index+1,[H|Acc],X).

%%%%%%%%%%%%%%%%%%%%%%
%%   Question 10
%%%%%%%%%%%%%%%%%%%%%%

split(L,N,L1,L2) :-
	makeSmallerList(L,N,L1),
	findall(X,(member(X,L),\+member(X,L1)),L2).

makeSmallerList(L,N,X) :-
	makeSmallerList(L,N,0,[],X).

makeSmallerList(L,N,N,X,X).

makeSmallerList([],N,_,X,X).

makeSmallerList([H|T],N,Sn,Acc,X) :-
	Sn < N, 
	Nn is Sn + 1,
	append(Acc,[H],NAcc),
	makeSmallerList(T,N,Nn,NAcc,X).