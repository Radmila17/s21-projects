SELECT * FROM person_visits pv;
INSERT INTO person_visits
VALUES (
		(SELECT max(id) FROM person_visits)+1,(SELECT id FROM person p WHERE name = 'Denis'), 
		(SELECT id FROM pizzeria WHERE name LIKE 'Domino%'), 
		'2022-02-24' ),
		((SELECT max(id) FROM person_visits)+2,(SELECT id FROM person p WHERE name = 'Irina'), 
		(SELECT id FROM pizzeria WHERE name LIKE 'Domino%'), 
		'2022-02-24' );
SELECT * FROM person_visits pv;

SELECT count(*)=2 AS CHECK
 FROM person_visits
 WHERE visit_date = '2022-02-24'
   AND person_id IN (6, 4)
   AND pizzeria_id = 2;