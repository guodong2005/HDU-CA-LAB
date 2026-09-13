#include <stdint.h>

#define T 4
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)
#define MAX_NODES 4000
#define N 10000

static uint32_t keys[MAX_NODES][MAX_KEYS];
static uint16_t child[MAX_NODES][MAX_CHILDREN];
static uint8_t count[MAX_NODES];
static uint8_t leaf[MAX_NODES];
static uint16_t nodes;
static uint16_t root;

static uint32_t rng_state = 0x13579bdfu;
static uint32_t next_key(void) {
  rng_state = rng_state * 1664525u + 1013904223u;
  return rng_state ^ (rng_state >> 16);
}

static uint16_t new_node(uint8_t is_leaf) {
  uint16_t id = nodes++;
  count[id] = 0;
  leaf[id] = is_leaf;
  return id;
}

static void split_child(uint16_t parent, uint32_t slot) {
  uint16_t full = child[parent][slot];
  uint16_t right = new_node(leaf[full]);
  uint32_t promoted = keys[full][T - 1];
  count[right] = T - 1;
  for (uint32_t j = 0; j < T - 1; ++j) keys[right][j] = keys[full][j + T];
  if (!leaf[full]) for (uint32_t j = 0; j < T; ++j) child[right][j] = child[full][j + T];
  count[full] = T - 1;
  for (uint32_t j = count[parent]; j > slot; --j) child[parent][j + 1] = child[parent][j];
  child[parent][slot + 1] = right;
  for (uint32_t j = count[parent]; j > slot; --j) keys[parent][j] = keys[parent][j - 1];
  keys[parent][slot] = promoted;
  count[parent]++;
}

static void insert_nonfull(uint16_t node, uint32_t key) {
  int32_t i = (int32_t)count[node] - 1;
  if (leaf[node]) {
    while (i >= 0 && key < keys[node][i]) { keys[node][i + 1] = keys[node][i]; --i; }
    if (i >= 0 && keys[node][i] == key) return;
    keys[node][i + 1] = key; count[node]++;
    return;
  }
  while (i >= 0 && key < keys[node][i]) --i;
  ++i;
  if (i < (int32_t)count[node] && key == keys[node][i]) return;
  uint16_t next = child[node][i];
  if (count[next] == MAX_KEYS) {
    split_child(node, i);
    if (key > keys[node][i]) ++i;
    else if (key == keys[node][i]) return;
  }
  insert_nonfull(child[node][i], key);
}

static void insert_key(uint32_t key) {
  uint16_t old_root = root;
  if (count[old_root] == MAX_KEYS) {
    uint16_t new_root = new_node(0);
    root = new_root; child[new_root][0] = old_root;
    split_child(new_root, 0);
    insert_nonfull(new_root, key);
  } else insert_nonfull(old_root, key);
}

static uint32_t traversal_count;
static uint32_t traversal_sum;
static uint32_t previous;
static uint32_t ordered;
static void walk(uint16_t node) {
  for (uint32_t i = 0; i < count[node]; ++i) {
    if (!leaf[node]) walk(child[node][i]);
    if (traversal_count && previous >= keys[node][i]) ordered = 0;
    previous = keys[node][i]; traversal_count++; traversal_sum += keys[node][i];
  }
  if (!leaf[node]) walk(child[node][count[node]]);
}

int main(void) {
  root = new_node(1); nodes = 1;
  uint32_t expected_sum = 0;
  for (uint32_t i = 0; i < N; ++i) { uint32_t key = next_key(); expected_sum += key; insert_key(key); }
  traversal_count = 0; traversal_sum = 0; previous = 0; ordered = 1; walk(root);
  if (traversal_count != N || traversal_sum != expected_sum || !ordered || nodes >= MAX_NODES) goto fail;
  __asm__ volatile ("ebreak");
  for (;;) {}
fail:
  for (;;) {}
}
