//
//  PeopleList.cpp
//  cs32_project3
//
//  Created by CCS on 24/7/17.
//  Copyright © 2017 CCS. All rights reserved.
//


#include <string>
#include <iostream>
#include "PeopleList.h"

PeopleList:: PeopleList() {
    head = nullptr;
}

PeopleList:: PeopleList(const PeopleList& rhs) {
    // copy constuctor
    // since newly created, no need to deconstruct
    this->head = nullptr;
    if (rhs.head == nullptr) return;
    
    Node *p;
    Node *tmp;
    Node *q = rhs.head;
    
    head = new Node;
    head->fn = q->fn;
    head->ln = q->ln;
    head->val = q->val; // copy Node q into this->head
    head->prev = nullptr;
    p = head;
    q = q->next;
    
    while (q != nullptr) {
        tmp = new Node;
        tmp->fn = q->fn;
        tmp->ln = q->ln;
        tmp->val = q->val; // copy Node q into tmp
        
        p->next = tmp; // p --> tmp
        tmp->prev = p; // p <-> tmp
        
        p = p->next;   // ie. p = tmp
        q = q->next;
    }
    p->next = nullptr;
}

const PeopleList& PeopleList:: operator=(const PeopleList& rhs) { // checked
    if (this == &rhs) return *this;
    
    // deconstruct
    // delete orignal PeopleList to avoid memory leak
    Node *p;
    while (head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
    // actually the previous block of codes can be changed to
    // this -> ~PeopleList();
    
    // create a new PeopleList using the copy constructor
    PeopleList *tmp_list = new PeopleList(rhs);
    head = tmp_list->head;
    return *this;
}

PeopleList:: ~PeopleList() {
    Node *p;
    while (head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
}

bool PeopleList:: empty() const {
    return head == nullptr;
}

int PeopleList:: size() const { // checked
    int ret = 0;
    Node *p = head;
    while (p != nullptr) {
        ++ret;
        p = p->next;
    }
    return ret;
}

bool PeopleList:: add(const std::string& firstName, const std::string& lastName, const InfoType& value) {
    
    if (contains(firstName, lastName))
        return false;
    
    
    
    if (head == nullptr) { // empty linkedList
        head = new Node;
        head->fn = firstName;
        head->ln = lastName;
        head->val = value;
        head->prev = nullptr;
        head->next = nullptr;
        return true;
    }
    
    Node *tmp;
    tmp = new Node;
    tmp->fn = firstName;
    tmp->ln = lastName;
    tmp->val = value;
    
    if (lastName < head->ln || (lastName == head->ln && firstName < head->fn)) {
        
        //insert the tmp Node to the front of the linkedList
        tmp->prev = nullptr;
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
        return true;
    }
    
    for (Node *p = head; p != nullptr; p = p->next) {
        if (lastName < p->ln || (lastName == p->ln && firstName < p->fn) ) {
            
            // insert the node tmp before p
            tmp->prev = p->prev;
            tmp->next = p;
            p->prev->next = tmp;
            p->prev = tmp;
            return true;
        }
        
        if (p->next == nullptr) {
            
            // insert the node to the end of the linkedList
            tmp->prev = p;
            tmp->next = nullptr;
            p->next = tmp;
            return true;
        }
    }
    return true; // just to eliminate warning, this statement should never be called
}

bool PeopleList:: change(const std::string &firstName, const std::string &lastName, const InfoType& value) {
    if (!contains(firstName, lastName))
        return false;
    
    for (Node *p = head; p != nullptr; p = p->next) {
        if (p->fn == firstName && p->ln == lastName) {
            p->val = value;
            return true;
        }
    }
    return true; // just to eliminate warning, this statement should never be called
}

bool PeopleList:: addOrChange(std::string firstName, std::string lastName, const InfoType& value) {
    if (!contains(firstName, lastName))
        return add(firstName, lastName, value);
    return change(firstName, lastName, value);
}

bool PeopleList:: remove(const std::string& firstName, const std::string& lastName) {
    if (!contains(firstName, lastName))
        return false;
    
    for (Node *p = head; p !=nullptr; p = p->next) {
        if (p->fn == firstName && p->ln == lastName) { // person found
            
            if (p == head) {
                head = p->next;
                head->prev = nullptr;
                delete p;
                return true;
            }
            
            if (p->next == nullptr) {
                p->prev->next = nullptr;
                delete p;
                return true;
            }
            
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            return true;
        }
    }
    return true; // just to eliminate warning, this statement should never be called
}

bool PeopleList:: contains(const std::string firstName, const std::string lastName) const {
    
    if (head == nullptr) return false;
    
    for (Node *p = head; p != nullptr; p = p->next)
        if (p->fn == firstName && p->ln == lastName)
            return true;
    
    return false;
}

bool PeopleList:: lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const {
    
    for (Node *p = head; p != nullptr; p = p->next)
        if (p->fn == firstName && p->ln == lastName) {
            value = p->val;
            return true;
        }
    
    return false;
}


bool PeopleList:: get(int i, std::string& firstName, std::string& lastName, InfoType& value) const {
    if (i < 0 || i >= size())
        return false;
    
    Node *p = head;
    while (i) {
        p = p->next;
        i--;
    }
    
    firstName = p->fn;
    lastName = p->ln;
    value = p->val;
    return true;
}

void PeopleList:: swap(PeopleList& other) {
    Node *tmp = other.head;
    other.head = this->head;
    this->head = tmp;
}

bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result) {
    bool ret = true;
    PeopleList ans;
    
    for (int n1 = 0; n1 < m1.size(); n1++) {
        std::string f1;
        std::string l1;
        InfoType v1;
        m1.get(n1, f1, l1, v1); // get a name from m1
        
        bool addOrNot = true;
        for (int n2 = 0; n2 < m2.size(); n2++) {
            // to check whether this name should be added to the result
            
            std::string f2;
            std::string l2;
            InfoType v2;
            m2.get(n2, f2, l2, v2);
            
            if (f1 == f2 && l1 == l2) { // name exists in both m1 & m2
                if (v1 == v2) // if with the same value, then the name should be added
                    addOrNot = true;
                else {
                    addOrNot = false;
                    ret = false;
                }
                break;
            }
        }
        
        if (addOrNot) ans.addOrChange(f1, l1, v1);
        // add this name to ans(result)
    }
    
    for (int n2 = 0; n2 < m2.size(); n2++) {
        std::string f2;
        std::string l2;
        InfoType v2;
        m2.get(n2, f2, l2, v2); // get a name from m2
        
        bool addOrNot = true;
        for (int n1 = 0; n1 < m1.size(); n1++) {
            // to check whether this name should be added to the result
            
            std::string f1;
            std::string l1;
            InfoType v1;
            m1.get(n1, f1, l1, v1);
            
            if (f2 == f1 && l2 == l1) { // name exists in both m1 & m2
                addOrNot = false;
                // either the name has been added to result previously
                // or the name should not be added to result
                break;
            }
        }
        
        if (addOrNot) ans.addOrChange(f2, l2, v2);
        // add this name to ans(result)
    }
    
    result = ans;
    return ret;
}

void search (const std::string& fsearch, const std::string& lsearch,
             const PeopleList& p1, PeopleList& result) {
    PeopleList ans;
    
    for (int n = 0; n < p1.size(); n++) {
        std::string f;
        std::string l;
        InfoType v;
        p1.get(n, f, l, v); // get a name from p1
        
        if (fsearch != "*" && fsearch != f) continue;
        if (lsearch != "*" && lsearch != l) continue;
        
        ans.add(f, l, v);
    }
    result = ans;
}

