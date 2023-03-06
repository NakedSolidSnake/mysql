create table if not exists person_tb (
    id bigint primary key auto_increment,
    name varchar (255) not null,
    age int not null
);

insert into person_tb (name, age) values ('Cristiano', 36);