Для обращения автомата А2 требуется:
  * Заданный (построенный) FSM_with_trans автомат А2
  * вызывать функции в следующем порядке:
      *   Node* get_u_from_z(Node* root, int* z, int i, FSM_with_trans& A2, int wall);
      *   void mark_to_delete(Node* root);
      *   void delete_tree_except_of_start_where_is_need(Node* root, bool& deleted);

Этап с удалением ветви вверх был отделён от функции построения дерева get_u_from_z();
