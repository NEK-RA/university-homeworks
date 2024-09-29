create database if not exists shop;
use shop;
-- TODO tools (name, price, amount)
create table if not exists tools(
    id int not null auto_increment,
    title varchar(30) not null,
    amount int not null,
    price float not null,
    primary key (id)
);
insert into tools values
                      (1,"Hammer", 3, 489.79),
                      (2, "Saw", 10, 280),
                      (3, "Nails (1kg)", 1, 329.99);
-- TODO orders (id from cookie, tool id, date)
create table if not exists orders(
    id int not null auto_increment,
    user_id varchar(10) not null ,
    tool_id int not null,
    date datetime not null,
    primary key (id),
    foreign key (tool_id) references tools (id)
);
