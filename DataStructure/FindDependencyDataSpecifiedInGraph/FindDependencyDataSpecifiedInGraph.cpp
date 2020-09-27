/*
*** 회사 안에 여러개의 프로젝트 중에서 몇몇 프로젝트들은 특정 프로젝트가 완료 되어야만
*** 진행 할 수 있는 프로젝트가 있다. 프로젝트의 목록과 각 프로젝트간 의존 여부를 input
*** 으로 받고 의존도에 입각한 프로젝트의 진행 순서를 출력하라.
*** projects: a, b, c, d, e, f, g
*** dependencies: (f,a), (f,b), (f,c), (b,a), (c,a), (a,e), (b,e), (d,g)
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>

template <typename T>
struct LinkedList
{
    struct LinkedListNode
    {
        LinkedListNode() : mNextLinkedListNode(nullptr) {}
        LinkedListNode(T data) : mLinkedListNodeData(data), mNextLinkedListNode(nullptr) {}

        T mLinkedListNodeData;
        LinkedListNode* mNextLinkedListNode;
    }; // end LinkedListNode struct

    LinkedList() : mLinkedListheader(new LinkedListNode()) {}
    void AddLinkedListNode(T data)
    {
        LinkedListNode* addNode = new LinkedListNode(data);
        LinkedListNode* iter = mLinkedListheader;
        while (iter->mNextLinkedListNode != nullptr)
        {
            iter = iter->mNextLinkedListNode;
        }

        iter->mNextLinkedListNode = addNode;
    }
    bool IsEmptyLinkedList()
    {
        LinkedListNode* iter = mLinkedListheader->mNextLinkedListNode;
        
        return iter == nullptr ? true : false;
    }

    LinkedListNode* mLinkedListheader;
}; // end LinkedList struct;

struct Project
{
    Project() : mProjectName(""), mProjectDependencies(nullptr), mProjectMarked(false) {}
    Project(const std::string name) : mProjectName(name), mProjectDependencies(new LinkedList<Project>()), mProjectMarked(false) {}
    void AddDependency(const Project& project) const;

    std::string mProjectName;
    LinkedList<Project>* mProjectDependencies;
    bool mProjectMarked;
}; // end Project struct

void Project::AddDependency(const Project& project) const
{
    LinkedList<Project>::LinkedListNode* iter = mProjectDependencies->mLinkedListheader;
    while (iter != nullptr)
    {
        iter = iter->mNextLinkedListNode;
    }

    if (iter == nullptr)
    {
        mProjectDependencies->AddLinkedListNode(project);
    }
}

struct ProjectManager
{
    ProjectManager() {}
    ProjectManager(std::vector<std::string> names, std::vector<std::vector<std::string>> dependencies)
    {
        BuildProjects(names);
        AddDependencies(dependencies);
    }
    void BuildProjects(std::vector<std::string> names);
    void AddDependencies(std::vector<std::vector<std::string>> dependencies) const;
    Project* BuildOrder() const;
    void BuildOrderByProject(Project project, Project* ordered) const;
    void InitMarkingFlags() const;
    Project FindProject(std::string name) const;

    std::map<std::string, Project>* mProjects;
}; // end ProjectManager struct

void ProjectManager::BuildProjects(std::vector<std::string> names)
{
    mProjects = new std::map<std::string, Project>();
    for (int index = 0; index < names.size(); ++index)
    {
        Project addProject(names[index]);
        mProjects->insert(std::make_pair(names[index], addProject));
    }
}

void ProjectManager::AddDependencies(std::vector<std::vector<std::string>> dependencies) const
{
    for (std::vector<std::string> dependency : dependencies)
    {
        Project before = FindProject(dependency[0]);
        Project after = FindProject(dependency[1]);
        after.AddDependency(before);
    }
}

int index;
Project* ProjectManager::BuildOrder() const
{
    InitMarkingFlags();
    Project* ordered = new Project[mProjects->size()];
    index = 0;
    std::map<std::string, Project>::iterator iter = mProjects->begin();
    for (; iter != mProjects->end(); ++iter)
    {
        BuildOrderByProject(iter->second, ordered);
    }

    return ordered;
}

void ProjectManager::BuildOrderByProject(Project project, Project* ordered) const
{
    if (!project.mProjectDependencies->IsEmptyLinkedList())
    {
        LinkedList<Project>::LinkedListNode* iter = project.mProjectDependencies->mLinkedListheader->mNextLinkedListNode;
        while (iter != nullptr)
        {
            BuildOrderByProject(iter->mLinkedListNodeData, ordered);
            iter = iter->mNextLinkedListNode;
        }
    }

    if (!project.mProjectMarked)
    {
        project.mProjectMarked = true;
        ordered[index] = project;
        ++index;
    }
}

void ProjectManager::InitMarkingFlags() const
{
    std::map<std::string, Project>::iterator iter = mProjects->begin();
    for (; iter != mProjects->end(); ++iter)
    {
        iter->second.mProjectMarked = false;
    }
}

Project ProjectManager::FindProject(std::string name) const
{
    std::map<std::string, Project>::iterator iter = mProjects->find(name);

    return iter->second;
}

int main()
{
    std::vector<std::string> projects = { "a", "b", "c", "d", "e", "f", "g" };
    std::vector<std::vector<std::string>> dependencies = { {"f", "a"}, {"f", "b"}, {"f", "c"}, {"b", "a"}, {"c", "a"}, {"a", "e"}, {"b", "e"}, {"d", "g"} };
    ProjectManager pm(projects, dependencies);
    Project* ps = pm.BuildOrder();
    for (int index = 0; index < _msize(ps) / sizeof(ps); ++index)
    {
        if (ps->mProjectName == "")
        {
            std::cout << ps[index].mProjectName << " ";
        }
    }

    return 0;
}
