struct list{
	void *node;
	struct list *next;
};

void append(struct list **head, void *node){
	struct list *temp = (struct list*)malloc(sizeof(struct list));
	temp -> node = node;
	temp -> next = NULL;

	if(!(*head))
		*head = temp;

	else {
		struct list *current = *head;
		while(current -> next)
			current = current -> next;

		current -> next = temp;
	}
}

struct list * popFirst(struct list **head){
	if(*head){
		struct list *temp = *head;
		(*head) = (*head) -> next;
		return temp;
	}
	return NULL;
}

void clearList(struct list **head){
	struct list *prev = NULL;
	while(*head){
		prev = *head;
		(*head) = (*head) -> next;

		free(prev);
	}
}

void deleteList(struct list **head){
	clearList(&(*head));
	free(*head);
}
