/*First query with IN*/
SELECT name
FROM pizzeria p 
WHERE p.id NOT IN (SELECT pv.pizzeria_id  FROM person_visits pv );

/*Second query with EXISTS */
SELECT name
FROM pizzeria p 
WHERE EXISTS (SELECT 1  FROM person_visits pv WHERE p.id = pv.pizzeria_id)!=TRUE;