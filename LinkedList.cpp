#include <iostream>
using namespace std;

struct linked_list{
    int number;
    struct linked_list *next;
};

typedef struct linked_list node; 

void create(node *list){
    cin >> list -> number;

    if(list -> number == -9){
        list->next = NULL;
    }else{
        list -> next = (node*) malloc (sizeof(node));
        create(list -> next);
    }
}

void print(node *list){
    cout << list->number << " ";
    if(list -> next == NULL){
        return ;
    }else{
        print(list -> next);
    }
    cout << endl;
}

void insertAtBeginning(node **list){
    node *new_node;
    new_node = (node*) malloc (sizeof(node));

    cout << "Enter the first node you want to insert : ";
    cin >> new_node->number;
    new_node->next = *list;
    *list = new_node;
}

void insertAtEnd(node **list){
    node *new_node;
    new_node = (node *) malloc (sizeof(node));

    if((*list) -> next == NULL){
        cout << "Enter the last node you want to insert : ";
        cin >> new_node->number;
        (*list) -> next = new_node;
        new_node -> next = NULL;

        return ;
    }else{
        insertAtEnd(&((*list) -> next));
    }
    
}

void insertBeforeValue(node **list){
    node *new_node, *ptr, *preptr;
    new_node = (node *) malloc (sizeof(node));
    ptr = *list;
    preptr = NULL;

    int target;

    cout << "Enter the node before where you want to insert : ";
    cin >> target;
    
    while(ptr != NULL && ptr->number != target){
        preptr = ptr;
        ptr = ptr->next;
    }

    if(ptr == NULL){
        cout << "Node with given value not found. " << endl;
        return;
    }

    cout << "Enter the number to insert : ";
    cin >> new_node->number;

    if(preptr == NULL){
        new_node->next = *list;
        *list = new_node;
    } else {
        preptr->next = new_node;
        new_node->next = ptr;
    }
    
}

void insertAfterValue(node **list){
    node *new_node, *ptr;
    new_node = (node *) malloc (sizeof(node));
    ptr = *list;

    cout << "Enter the node after which you want to insert : ";
    int target;
    cin >> target;

    while(ptr != NULL && ptr->number != target){
        ptr = ptr->next;
    }

    if(ptr == NULL){
        cout << "Node with given value not found. " << endl;
        return;
    }

    cout << "Enter the number to insert : ";
    cin >> new_node->number;

    new_node->next = ptr->next;
    ptr->next = new_node;
}

void deleteFirstNode(node **list){
    if(*list == NULL){
        cout << "List is already empty." << endl;
        return;
    }

    node *temp = *list;
    *list = (*list)->next;
    free(temp);
}

void deleteLastNode(node **list){
    if(*list == NULL){
        cout << "List is already empty." << endl;
        return;
    }

    // If there is only one node
    if((*list)->next == NULL){
        free(*list);
        *list = NULL;
        return;
    }

    // Traverse the list to find the second last node
    node *secondLast = *list;
    while(secondLast->next->next != NULL){
        secondLast = secondLast->next;
    }

    // Delete the last node
    free(secondLast->next);
    secondLast->next = NULL;
}

void deleteNodeAfter(node **list){
    if(*list == NULL || (*list)->next == NULL){
        cout << "Cannot delete node. Either list is empty or it has only one node." << endl;
        return;
    }

    int target;
    cout << "Enter the node value after which you want to delete : ";
    cin >> target;

    node *prevNode = *list;
    while(prevNode != NULL && prevNode->number != target){
        prevNode = prevNode->next;
    }

    if(prevNode == NULL || prevNode->next == NULL){
        cout << "Node with given value not found or it is the last node." << endl;
        return;
    }

    // Store the node to be deleted in a temporary pointer
    node *toBeDeleted = prevNode->next;
    // Update the next pointer of the previous node to skip the node to be deleted
    prevNode->next = prevNode->next->next;
    // Free the memory occupied by the node to be deleted
    free(toBeDeleted);
}

void menu(node **list){
    int choice;

    while(choice != 8){
        cout << "SOME CHOICES : " << endl;
        cout << "1. Insert at first" << endl;
        cout << "2. Insert at last" << endl;
        cout << "3. Insert before a node" << endl;
        cout << "4. Inset after a node" << endl;
        cout << "5. Delete the first node" << endl;
        cout << "6. Delete the last node" << endl;
        cout << "7. Delete after a node" << endl; 
        cout << "8. Exit" << endl;
        cout << "Please select your choice : ";
        cin >> choice;

        switch(choice){
            case 1:
                insertAtBeginning(list);
                break;
            case 2:
                insertAtEnd(list);
                break;
            case 3: 
                insertBeforeValue(list);
                break;
            case 4: 
                insertAfterValue(list);
                break;
            case 5: 
                deleteFirstNode(list);
                break;
            case 6:
                deleteLastNode(list);
                break;
            case 7:
                deleteNodeAfter(list);
                break;
            case 8:
                cout <<"Exiting...." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }

        cout << "The list is : ";
        print(*list);
    }
}

int main(){
    node *head;
    head = (node *) malloc (sizeof (node));

    cout << "Enter the numbers (Enter -9 at the end): ";
    create(head);
    print(head);
    menu(&head);

    return 0;
}