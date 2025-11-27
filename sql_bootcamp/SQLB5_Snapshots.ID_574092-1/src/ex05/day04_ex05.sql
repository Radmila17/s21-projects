CREATE OR REPLACE VIEW v_price_discount AS
SELECT p.name AS name,
		m.pizza_name,
		m.price,
		(m.price-m.price*0.1)::int AS discount_price
FROM menu m 
JOIN person_order po ON po.menu_id = m.id
JOIN person p ON p.id = po.person_id
ORDER BY name, pizza_name;

SELECT * FROM v_price_discount;