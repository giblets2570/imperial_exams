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

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    26
%
%%%%%%%%%%%%%%%%%%%%%%%%%

combination(N,L,X):-
	combination(N,L,[],X,0).

combination(N,_,X,X,N).

combination(N,[H|T],Acc,X,K):-
	K < N,
	KK is K + 1,
	append(Acc,[H],Nacc),
	combination(N,T,Nacc,X,KK).

combination(N,[_|T],Acc,X,K):-
	K < N,
	combination(N,T,Acc,X,K).

combination2(N,L,X):-
	combination2(N,L,X,0).

combination2(N,_,[],N).

combination2(N,[H|T1],[H|T2],K):-
	K < N,
	KK is K+1,
	combination2(N,T1,T2,KK).

combination2(N,[H|T],L,K):-
	K < N,
	combination2(N,T,L,K).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    27
%
%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%% a)

combination3(N,L,X,RestL):-
	combination3(N,L,X,RestL,0).

combination3(N,_,[],[],N).

combination3(N,[H|T1],[H|T2],L,K):-
	K < N,
	KK is K+1,
	combination3(N,T1,T2,L,KK).

combination3(N,[H|T1],L,[H|T2],K):-
	K < N,
	combination3(N,T1,L,T2,K).

group3(L,G1,G2,G3):-
	combination3(2,L,G1,R1),
	combination3(3,R1,G2,R2),
	combination3(4,R2,G3,_).

%%%%%%%%%%%%%%%%%%%%%%%% b)

group([],[],[]).

group(L,[N|T],[G|T2]):-
	combination3(N,L,G,R),
	group(R,T,T2).

%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    28
%
%%%%%%%%%%%%%%%%%%%%%%%%%

max_length([L],N):-
	length(L,N).

max_length([L1,L2|T],X):-
	length(L1,N1),
	length(L2,N2),
	N1>N2,
	max_length([L1|T],X).

max_length([L1,L2|T],X):-
	length(L1,N1),
	length(L2,N2),
	N1=<N2,
	max_length([L2|T],X).

lsort(L,X):-
	lsort(L,X,1),
	!.

lsort(L,[],NN):-
	max_length(L,N),
	NN is N+1.

lsort(L,RT,K):-
	KK is K+1,
	findall(X,(member(X,L),length(X,K)),R),
	lsort(L,T,KK),
	append(R,T,RT).

%%%%%%%%%%%%%%%%%%%%%%%%%%

frequency(N,L,X):-
	frequency(N,L,X,0).

frequency(_,[],X,X).

frequency(N,[H|T],X,K):-
	length(H,N),
	KK is K+1,
	frequency(N,T,X,KK).

frequency(N,[H|T],X,K):-
	length(H,M),
	M\=N,
	frequency(N,T,X,K).

max_freq(