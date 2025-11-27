
// Definition for a Node
class Node
{
  public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution
{
  public:
    Node* flatten(Node* head) // Time: O(n); Space: O(1)
    {
        if (!head)
            return nullptr;

        Node* curr = head;
        while (curr)
        {
            // If the node has a child, we insert the child list here
            if (curr->child)
            {
                Node* nextNode = curr->next;
                Node* childNode = curr->child;

                // 1. Find the tail of the child list
                Node* childTail = childNode;
                while (childTail->next) // Find the tail of the child node
                {
                    childTail = childTail->next;
                }

                // 2. Connect child tail to original next node
                childTail->next = nextNode;
                if (nextNode)
                {
                    nextNode->prev = childTail;
                }

                // 3. Connect current node to child head
                curr->next = childNode;
                childNode->prev = curr;

                // 4. Nullify child pointer
                curr->child = nullptr;
            }
            curr = curr->next;
        }

        return head;
    }
};