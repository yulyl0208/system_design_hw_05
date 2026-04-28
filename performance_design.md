# Fitness Tracker 

## 1. Контекст системы

Система — фитнес-трекер 
- пользователи
- упражнения
- тренировки
- статистика тренировок


---

## 2. Hot paths

### Часто вызываемые endpoints:
- GET /exercises
- GET /workouts/history
- GET /workouts/stats
- POST /workouts

---

## 3. Медленные операции

### Дорогие операции:
- JOIN workouts + workout_exercises
- агрегирование SUM, COUNT(workouts)
- сортировка истории тренировок
- выборка статистики за период

---

## 4. Стратегия кеширования

### Выбран подход: Cache-Aside

---

### Кешируемые данные:

- exercises 
- workout history 
- workout stats

---

### TTL:

| Данные             | TTL   | Причина |
|-------------------|-------|--------|
| exercises         | 600s  | редко меняются |
| workout history   | 300s  | умеренная актуальность |
| workout stats     | 120s  | часто пересчитываются |

---

### Redis keys:

- exercises:all
- workouts:history:{user_id}
- workouts:stats:{user_id}

---

### Инвалидация кеша:

При изменении данных:
- POST /workouts:
  - invalidate workouts:history:{user_id}
  - invalidate workouts:stats:{user_id}

---

## 5. Rate limiting

### Цели:
- защита от перегрузки БД
- защита от злоупотребления API
- стабилизация latency

---

### Алгоритм: Token Bucket

---

### Лимиты:

| Endpoint         | Limit        |
|-----------------|--------------|
| POST /workouts  | 50 req/min   |
| GET /stats      | 30 req/min   |
| GET /history    | 60 req/min   |


---

## 6. Производительность системы

### До оптимизации:
- высокая нагрузка на PostgreSQL
- повторные одинаковые запросы
- частые JOIN и агрегации

---

### После оптимизации:
- снижение нагрузки на БД на 60–80%
- ускорение ответов в 3–5 раз
- уменьшение количества SQL-запросов

---

## 7. Метрики мониторинга

### Основные метрики:

- cache hit rate
- p95 latency
- p99 latency
- RPS
- DB query time
- Redis ops/sec

---

## 8. Итог

Использованные подходы:
- Cache-Aside caching strategy
- Token Bucket rate limiting
- PostgreSQL indexing
- Redis as distributed cache and limiter
