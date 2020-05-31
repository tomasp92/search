SELECT title FROM movies 
WHERE id IN (SELECT movie_id fROM stars  
WHERE person_id IN (SELECT id  FROM people 
WHERE name = "Johnny Depp"))AND id IN (SELECT movie_id fROM stars  
WHERE person_id IN (SELECT id  FROM people 
WHERE name = "Helena Bonham Carter"));