/*Удалить посещения одного и того же человека. Если он посетил одну пиццерию несколько раз, 
 он будет считаться одним человеком */
WITH unic_pv AS
		(SELECT pv.person_id, pv.pizzeria_id 
		FROM person_visits pv
		GROUP BY pv.person_id, pv.pizzeria_id),
	female_visits AS 
		(SELECT upv.pizzeria_id, count(*) AS count_of_female
		FROM unic_pv upv
		JOIN person p ON p.id = upv.person_id AND p.gender LIKE 'fem%'
		GROUP BY upv.pizzeria_id),
	male_visits AS 
		(SELECT upv.pizzeria_id ,  count(*) AS count_of_male
		FROM unic_pv upv
		JOIN person p ON p.id = upv.person_id AND p.gender LIKE 'mal%'
		GROUP BY upv.pizzeria_id ),
	all_gender_counts AS 
		(SELECT 
			COALESCE (fv.pizzeria_id, mv.pizzeria_id )AS pizzeria_id, 
			COALESCE (fv.count_of_female, 0) AS count_of_female, 
			COALESCE(mv.count_of_male, 0) AS count_of_male 
		FROM female_visits fv
		FULL JOIN male_visits mv
		ON fv.pizzeria_id = mv.pizzeria_id)
SELECT piz.name AS pizzeria_name
FROM pizzeria piz
JOIN all_gender_counts agc ON piz.id = agc.pizzeria_id AND agc.count_of_female!= agc.count_of_male
ORDER BY piz."name";	

/*,
-- Подсчет посещений по полу и пиццериям
WITH visit_counts AS (
  SELECT 
    pv.pizzeria_id,
    p.gender,
    COUNT(*) AS visit_count
  FROM person_visits pv
  JOIN person p ON pv.person_id = p.id
  GROUP BY pv.pizzeria_id, p.gender
),
-- Отдельно посещения женщин
female_visits AS (
  SELECT pizzeria_id, visit_count
  FROM visit_counts
  WHERE gender = 'female'
),
-- Отдельно посещения мужчин
male_visits AS (
  SELECT pizzeria_id, visit_count
  FROM visit_counts
  WHERE gender = 'male'
),
-- Пиццерии чаще посещаемые женщинами
female_dominant AS (
  SELECT fv.pizzeria_id
  FROM female_visits fv
  LEFT JOIN male_visits mv ON fv.pizzeria_id = mv.pizzeria_id
  WHERE fv.visit_count > COALESCE(mv.visit_count, 0)
),
-- Пиццерии чаще посещаемые мужчинами
male_dominant AS (
  SELECT mv.pizzeria_id
  FROM male_visits mv
  LEFT JOIN female_visits fv ON mv.pizzeria_id = fv.pizzeria_id
  WHERE mv.visit_count > COALESCE(fv.visit_count, 0)
)
-- Итог: объединяем и сортируем
SELECT piz.name AS pizzeria_name
FROM pizzeria piz
JOIN female_dominant fd ON piz.id = fd.pizzeria_id
UNION ALL
SELECT piz.name AS pizzeria_name
FROM pizzeria piz
JOIN male_dominant md ON piz.id = md.pizzeria_id
ORDER BY pizzeria_name;


WITH female_table AS 
		(SELECT pv.pizzeria_id, count(*) AS count_of_female
		FROM person_visits pv 
		JOIN person p ON p.id = pv.person_id AND p.gender LIKE 'fem%'
		GROUP BY pv.pizzeria_id ),
	male_table AS 
		(SELECT pv.pizzeria_id ,  count(*) AS count_of_male
		FROM person_visits pv 
		JOIN person p ON p.id = pv.person_id AND p.gender LIKE 'mal%'
		GROUP BY pv.pizzeria_id ),
	gender_count_table AS 
		(SELECT ft.pizzeria_id, ft.count_of_female, mt.count_of_male
		FROM female_table ft
		FULL JOIN male_table mt ON ft.pizzeria_id = mt.pizzeria_id)
SELECT 
	COALESCE (ft.pizzeria_id, MT.pizzeria_id )AS pizzeria_id, 
	COALESCE (ft.count_of_female,0) AS count_of_female, 
	COALESCE(mt.count_of_male,0) AS count_of_male 
FROM female_table ft
right JOIN male_table mt ON ft.pizzeria_id = mt.pizzeria_id;
*/
		

		
