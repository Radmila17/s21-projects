SET enable_seqscan = OFF;

SELECT pizza_name, piz.name AS pizzeria_name
FROM menu m 
JOIN pizzeria piz ON m.pizzeria_id = piz.id;

EXPLAIN ANALYZE 
SELECT pizza_name, piz.name AS pizzeria_name
FROM menu m 
JOIN pizzeria piz ON m.pizzeria_id = piz.id;

SET enable_seqscan = ON;

-- Из-за маленького количества записей PostgreSql считает, что последжовательное сканирование
-- будет быстрее, чем использование индексов, поэтому я отключила на время последовательное сканирование
-- чтобы продемонстрировать работу индексов