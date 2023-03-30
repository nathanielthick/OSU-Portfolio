/*
* Nathaniel Thickett
* HW7
* 3/15/23
*/

/* course(course_number, course_name, credits) */

course(cs101,python, 2).
course(mth210, calculusI, 5).
course(cs120, web_design, 3).
course(cs200, data_structures, 4).
course(cs210, algorithms, 4).
course(wrt101, basic_writing, 3).

/* section(CRN, course_number) */

section(1522,cs101).
section(1122,cs101).
section(2322,mth210).
section(2421,cs120).
section(8522,mth210).
section(1621,cs200).
section(7822,mth210).
section(2822,cs210).
section(3522,wrt101).

/* place( CRN, building, time) */

place(1522,owen102,10).
place(1122,dear118,11).
place(2322,with210,11).
place(2421,cov216,15).
place(8522,kec1001,13).
place(1621,cov216,14).
place(7822,kec1001,14).
place(2822,owen102,13).
place(3522,with210,15).

/* enroll(sid, CRN) */

enroll(122,1522).
enroll(122,8522).
enroll(150,1522).
enroll(150,2421).
enroll(212,7822).
enroll(300,2822).
enroll(300,8522).
enroll(310,3522).
enroll(310,8522).
enroll(310,1621).
enroll(175,2822).
enroll(175,7822).
enroll(175,3522).
enroll(410,1621).
enroll(410,7822).
enroll(113,3522).

/* student(sid, student_name, major) */

student(122, mary, cs).
student(150, john, math).
student(212, jim, ece).
student(300, lee, cs).
student(310, pat, cs).
student(175, amy, math).
student(410, john, cs).
student(113, zoe, ece).

/*
* Schedule/4
* uses findall to find all courses the SID is enrolled in
* uses member to match courses with those CRNs
*/
schedule(Sid, CourseName, Building, Time) :-
  student(Sid, _, _),
  findall(CRN, enroll(Sid, CRN), CRNs),
  member(Course, CRNs),
  section(Course, CourseNum),
  course(CourseNum, CourseName, _),
  place(Course, Building, Time).

/*
* Schedule/3
* uses findall to find all courses the SID is enrolled in
* uses member to match courses with those CRNs, then gets names of courses
*/
schedule(Sid, Name, CourseName) :-
  student(Sid, Name, _),
  findall(CRN, enroll(Sid, CRN), CRNs),
  member(Course, CRNs),
  section(Course, CourseNum),
  course(CourseNum, CourseName, _).

/*
* Offer/4
* uses findall to find all CRNs with matching course num
* uses member to match courses with those CRNs, and uses place to find time of CRN
*/
offer(CourseNum, CourseName, CRN, Time) :-
  course(CourseNum, CourseName, _),
  findall(CRN1, section(CRN1, CourseNum), CRNs),
  member(CRN, CRNs),
  place(CRN, _, Time).

/*
* Conflict/3
* returns courses take by the same SID that occur at the same time
* returns false if no conflicts
*/
conflict(Sid, CRN1, CRN2) :-
  enroll(Sid, CRN1),
  enroll(Sid, CRN2),
  place(CRN1, _, Time),
  place(CRN2, _, Time),
  CRN1 \= CRN2.

/*
* Meet/2
* first case checks if two SIDs are in the same class
*/
meet(Sid1, Sid2) :-
  enroll(Sid1, CRN),
  enroll(Sid2, CRN),
  Sid1 \= Sid2.
  
/*
* Meet/2
* second case checks if SIDs have class back to back by comparing times
* checks if time of first student class +1 hour is equal to time of second student class
*/ 
meet(Sid1, Sid2) :-
  enroll(Sid1, CRN1),
  enroll(Sid2, CRN2),
  place(CRN1, Building, Time),
  place(CRN2, Building, Time2),
  Time + 1 =:= Time2,
  Sid1 \= Sid2.

/*
* Meet/2
* Same as second case, only compares times the other way around
* checks if time of second student class +1 hour is equal to time of first student class
*/ 
meet(Sid1, Sid2) :-
  enroll(Sid1, CRN1),
  enroll(Sid2, CRN2),
  place(CRN1, Building, Time),
  place(CRN2, Building, Time2),
  Time2 + 1 =:= Time,
  Sid1 \= Sid2.

/*
* Roster/2
* returns name of all students enrolled in CRN, or CRNs that Name is enrolled in
*/ 
roster(CRN, Name) :-
  findall(SID, enroll(SID, CRN), SIDs),
  member(StuId, SIDs),
  student(StuId, Name, _).

/*
* HighCredits/2
* Returns names of courses where credits >= 4
*/ 
highCredits(CName) :-
  course(_, CName, Credits),
  Credits >= 4.

/*
* rdup/2
* uses recursion to remove  duplicates from list, when two dups are found, calls itself with only 1 of the dups
*/ 
rdup([], []).
rdup([A], [A]).
rdup([A,A|T], C) :- rdup([A|T], C).
rdup([A,B|T1], [A|C]) :- A \= B, rdup([B|T1], C).

/*
* flat/2
* Uses recursion to produce a flat list, flat is called on head and tail of list
* append is used on results of each call to make 1 flat list
*/ 
flat([], []).
flat([H|T], F) :- 
    flat(H, FH),
    flat(T, FT),
    append(FH, FT, F).
flat(X, [X]) :- 
    X \= [].

/*
* flat/2
* Uses nth1 and a recursive call to collect all emebents at pos i|is in a list
*/ 
project([], _, []).
project([A|As], B, [C|Cs]) :- 
    nth1(A, B, C),
    project(As, B, Cs).
