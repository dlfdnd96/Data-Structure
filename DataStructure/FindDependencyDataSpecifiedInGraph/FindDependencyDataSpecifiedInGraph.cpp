/*
*** ȸ�� �ȿ� �������� ������Ʈ �߿��� ��� ������Ʈ���� Ư�� ������Ʈ�� �Ϸ� �Ǿ�߸�
*** ���� �� �� �ִ� ������Ʈ�� �ִ�. ������Ʈ�� ��ϰ� �� ������Ʈ�� ���� ���θ� input
*** ���� �ް� �������� �԰��� ������Ʈ�� ���� ������ ����϶�.
*** projects: a, b, c, d, e, f, g
*** dependencies: (f,a), (f,b), (f,c), (b,a), (c,a), (a,e), (b,e), (d,g)
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

class Project
{
public:
    Project(string name) : mName(name), mMarked(false) {}
    string GetName() const;
    void SetName(string const name);
    vector<Project> GetDependencies() const;
    bool GetMarked() const;
    void SetMarked(bool const mark);
    void AddDependency(Project& project);

private:
    string mName;
    vector<Project> mDependencies;
    bool mMarked;
}; // end Project class

string Project::GetName() const
{
    return mName;
}
void Project::SetName(string const name)
{
    this->mName = name;
}
vector<Project> Project::GetDependencies() const
{
    return this->mDependencies;
}
bool Project::GetMarked() const
{
    return this->mMarked;
}
void Project::SetMarked(bool const mark)
{
    this->mMarked = mark;
}

void Project::AddDependency(Project& project)
{
    vector<Project>::iterator it = std::find(mDependencies.begin(), mDependencies.end(), project);
    
    if (it == mDependencies.end())
    {
        mDependencies.push_back(project);
    }
}

class ProjectManager
{
public:
    ProjectManager(string* const names, string** const dependencies)
    {
        BuildProjects(names);
        AddDependencies(dependencies);
    }
    void BuildProjects(string* const names);
    void AddDependencies(string** dependencies);

private:
    map<string, Project> projects;
}; // end ProjectManager class

void ProjectManager::BuildProjects(string* const names)
{
    for (unsigned __int32 index = 0; index < names->length(); ++index)
    {
        projects.insert(std::pair<string, Project>(names[index], Project(names[index])));
    }
}

void ProjectManager::AddDependencies(string** dependencies)
{
    for (string* dependency : dependencies)
    {
        Project before = FindProject(dependency[0]);
        Project after = findProject(dependency[1]);
        after.AddDependency(before);
    }
}

int main()
{
    return 0;
}
