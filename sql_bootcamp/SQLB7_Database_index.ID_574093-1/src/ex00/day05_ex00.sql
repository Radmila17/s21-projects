SELECT * FROM person;
SELECT * FROM person_visits pv;
SELECT * FROM person_order po ;
SELECT * FROM menu m ;

CREATE INDEX IF NOT EXISTS idx_menu_pizzeria_id 
ON menu(pizzeria_id);

CREATE INDEX IF NOT EXISTS idx_person_order_person_id 
ON person_order(person_id);

CREATE INDEX IF NOT EXISTS idx_person_order_menu_id 
ON person_order(menu_id);

CREATE INDEX IF NOT EXISTS idx_person_visits_pizzeria_id 
ON person_visits(pizzeria_id);

CREATE INDEX IF NOT EXISTS idx_person_visits_person_id 
ON person_visits(person_id);



SELECT count(*) = 5 AS CHECK
FROM pg_indexes
WHERE indexname IN ('idx_menu_pizzeria_id',
                    'idx_person_order_person_id',
                    'idx_person_order_menu_id',
                    'idx_person_visits_person_id',
                    'idx_person_visits_pizzeria_id')
