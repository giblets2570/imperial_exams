%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    1
%
%%%%%%%%%%%%%%%%%%%%%%%%%

my_last([X],X).

my_last([H|T],X) :-
	my_last(T,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    8
%
%%%%%%%%%%%%%%%%%%%%%%%%%

compress([H|T],X):-
	compress(T,[H],X).

compress([],X,X).

compress([H|T],Acc,X):-
	my_last(Acc,R),
	H \= R,
	append(Acc,[H],Nacc),
	compress(T,Nacc,X).

compress([H|T],Acc,X):-
	my_last(Acc,R),
	H = R,
	compress(T,Acc,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    9
%
%%%%%%%%%%%%%%%%%%%%%%%%%

pack([H|T],X) :-
	pack(T,[H],[],X).

pack([],Dup,Acc,X):-
	append(Acc,[Dup],X).

pack([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H \= R,
	append(Acc,[Dup],Nacc),
	pack(T,[H],Nacc,X).

pack([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H = R,
	append(Dup,[H],Ndup),
	pack(T,Ndup,Acc,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    10
%
%%%%%%%%%%%%%%%%%%%%%%%%%

encode([H|T],X) :-
	encode(T,[H],[],X).

encode([],Dup,Acc,X):-
	length(Dup,N),
	Dup = [H|_],
	append(Acc,[[N,H]],X).

encode([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H \= R,
	length(Dup,N),
	append(Acc,[[N,R]],Nacc),
	encode(T,[H],Nacc,X).

encode([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H = R,
	append(Dup,[H],Ndup),
	encode(T,Ndup,Acc,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    11
%
%%%%%%%%%%%%%%%%%%%%%%%%%

encode_modified([H|T],X) :-
	encode_modified(T,[H],[],X).

encode_modified([],Dup,Acc,X):-
	length(Dup,N),
	N \= 1,
	Dup = [H|_],
	append(Acc,[[N,H]],X).

encode_modified([],Dup,Acc,X):-
	length(Dup,N),
	N = 1,
	Dup = [H],
	append(Acc,[H],X).

encode_modified([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H \= R,
	length(Dup,N),
	N = 1,
	append(Acc,[R],Nacc),
	encode_modified(T,[H],Nacc,X).

encode_modified([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H \= R,
	length(Dup,N),
	N \= 1,
	append(Acc,[[N,R]],Nacc),
	encode_modified(T,[H],Nacc,X).

encode_modified([H|T],Dup,Acc,X):-
	my_last(Dup,R),
	H = R,
	append(Dup,[H],Ndup),
	encode_modified(T,Ndup,Acc,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    14
%
%%%%%%%%%%%%%%%%%%%%%%%%%

dupli([],[]).

dupli([H|T1],[H,H|T2]):-
	dupli(T1,T2).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    15
%
%%%%%%%%%%%%%%%%%%%%%%%%%

dupli([],[],_).

dupli([H|T],NRe,N):-
	makelist(H,N,List),
	dupli(T,Re,N),
	append(List,Re,NRe).

makelist(_,0,[]).

makelist(X,N,[X|T]):-
	N>0,
	NN is N-1,
	makelist(X,NN,T).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    16
%
%%%%%%%%%%%%%%%%%%%%%%%%%

drop(L,N,X):
	drop(L,N,X,N).

drop([],_,[],_).

drop([H|T],N,[H|T2],K):-
	K>1,
	KK is K-1,
	drop(T,N,T2,KK).

drop([H|T],N,T2,K):-
	K=1,
	drop(T,N,T2,N).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    17
%
%%%%%%%%%%%%%%%%%%%%%%%%%

split(L,N,L1,L2):-
	split(L,N,L1,L2,0).

split([],_,[],[],_).

split([H|T],N,[H|T1],T2,K):-
	K < N,
	K1 is K+1,
	split(T,N,T1,T2,K1).

split([H|T],N,T1,[H|T2],K):-
	K >= N,
	K1 is K+1,
	split(T,N,T1,T2,K1).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    18
%
%%%%%%%%%%%%%%%%%%%%%%%%%

slice(L,N1,N2,X):-
	N2>N1,
	N4 is N1-1,
	N3 is N2-N4,
	split(L,N4,_,X1),
	split(X1,N3,X,_).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    19
%
%%%%%%%%%%%%%%%%%%%%%%%%%

rotate(L,N,X):-
	N >= 0,
	split(L,N,L1,L2),
	append(L2,L1,X).

rotate(L,N,X):-
	N < 0,
	length(L,Length),
	NN is Length + N,
	split(L,NN,L1,L2),
	append(L2,L1,X).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    20
%
%%%%%%%%%%%%%%%%%%%%%%%%%

remove_at(X,L,N,R):-
	remove_at(X,L,N,R,1).

remove_at(_,[],_,[],_).

remove_at(H,[H|T],N,T1,N):-
	NN is N+1,
	remove_at(_,T,N,T1,NN).

remove_at(X,[H|T],N,[H|T1],K):-
	K \= N,
	K1 is K+1,
	remove_at(X,T,N,T1,K1).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    21
%
%%%%%%%%%%%%%%%%%%%%%%%%%

insert_at(X,L1,N,L2):-
	remove_at(X,L2,N,L1).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    22
%
%%%%%%%%%%%%%%%%%%%%%%%%%

range(N,N,[N]).

range(N1,N2,[N1|T]):-
	N1 < N2,
	NN is N1 + 1,
	range(NN,N2,T).

