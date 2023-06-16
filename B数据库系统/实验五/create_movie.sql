drop table movie;
drop table showing;

create table movie
(
	movie_id int,
	title varchar(100),
	Primary Key (movie_id)
);

create table showing
(
	movie_id int,
	movie_time varchar(8),
	total_seats int,
	available_standard_seats int,
	Primary Key (movie_id, movie_time),
	Foreign Key (movie_id) references movie(movie_id)
);

insert into movie values (1, 'The Terminator' );
insert into movie values (2, 'James Bond' );
insert into movie values (3, 'The Matrix' );

insert into showing values (1, '1:00 PM', 40, 25);
insert into showing values (1, '4:00 PM', 30, 27);
insert into showing values (2, '12:30 PM', 50, 32);
insert into showing values (2, '7:30 PM', 75, 17);
insert into showing values (3, '9:30 PM', 100, 10);
