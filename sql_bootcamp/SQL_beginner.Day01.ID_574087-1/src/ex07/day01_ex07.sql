SELECT order_date, 
	concat(p.name, ' (age:', p.age , ')') AS person_informmation
FROM person_order po 
JOIN person p ON p.id = po.person_id
ORDER BY order_date, person_informmation ASC;