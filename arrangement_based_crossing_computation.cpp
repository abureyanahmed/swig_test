#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include<boost/tokenizer.hpp>
#include <sstream>
#include <cstdio>
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_rational.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_on_surface_with_history_2.h>
#include <CGAL/Arrangement_with_history_2.h>
#include <CGAL/Arr_simple_point_location.h>
#include "point_location_utils.h"
typedef CGAL::Cartesian<CGAL::Exact_rational>             Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel>                Traits_2;
typedef Traits_2::Point_2                                 Point_2;
typedef Traits_2::Curve_2                                 Segment_2;
typedef CGAL::Arrangement_with_history_2<Traits_2>        Arr_with_hist_2;
typedef Arr_with_hist_2::Curve_handle                     Curve_handle;
typedef CGAL::Arr_simple_point_location<Arr_with_hist_2>  Point_location;
#define MAX_NUMBER_OF_EDGES 100000

//int count_crossings(int & n, std::vector<double> & x, std::vector<double> & y, std::vector<int> & edg_u, std::vector<int> & edg_v)
std::vector<std::set<int> > get_edge_crossings(int n, std::vector<double> x, std::vector<double> y, std::vector<int> edg_u, std::vector<int> edg_v)
{
    if(edg_u.size()>MAX_NUMBER_OF_EDGES-10)
      std::cout << "Number of edges is large." << std::endl;
    std::vector<std::set<int> > res_set;
    Segment_2 segs[MAX_NUMBER_OF_EDGES];
    std::map<std::string,int> pnts_to_id;
    for(int i=0;i<edg_u.size();i++)
    {
      int u = edg_u[i];
      int v = edg_v[i];
      segs[i] = Segment_2(Point_2(x[u], y[u]), Point_2(x[v], y[v]));
      pnts_to_id[std::to_string(x[u])+","+std::to_string(y[u])+","+std::to_string(x[v])+","+std::to_string(y[v])] = i;
      pnts_to_id[std::to_string(x[v])+","+std::to_string(y[v])+","+std::to_string(x[u])+","+std::to_string(y[u])] = i;
      //std::cout << std::to_string(x[u])+","+std::to_string(y[u])+","+std::to_string(x[v])+","+std::to_string(y[v]) << std::endl;
      std::set<int> intersecting_edges;
      res_set.push_back(intersecting_edges);
    }
    //std::cout << pnts_to_id.size() << std::endl;
    Arr_with_hist_2   arr;
    insert(arr, segs, segs + edg_u.size());
    int count = 0;
    Arr_with_hist_2::Curve_iterator            cit;
    std::map<Arr_with_hist_2::Curve_iterator, int> addr_to_id;
    int i = 0;
    for (cit = arr.curves_begin(); cit != arr.curves_end(); ++cit)
    {
      //std::cout << &(*cit) << std::endl;
      addr_to_id[&(*cit)] = i++;
      int x = arr.number_of_induced_edges(cit);
      if(x>1)
      {
        count += (x-1);
      }
    }
    int number_of_crossings = count/2;
    // Print the arrangement edges, along with the list of curves that
    // induce each edge.
    Arr_with_hist_2::Edge_iterator                  eit;
    Arr_with_hist_2::Originating_curve_iterator     ocit;
    /*std::cout << "The arrangement is comprised of "
            << arr.number_of_edges() << " edges:" << std::endl;*/
    //Arr_with_hist_2::Curve_iterator first_edge = arr.curves_begin();
    for (eit = arr.edges_begin(); eit != arr.edges_end(); ++eit) {
      Arr_with_hist_2::Curve_iterator e1 = arr.originating_curves_begin(eit->next());
      Arr_with_hist_2::Curve_iterator e2 = arr.originating_curves_begin(eit);
      int ei1 = addr_to_id[&(*e1)];
      int ei2 = addr_to_id[&(*e2)];
      if((ei1 != ei2) && (edg_u[ei1] != edg_u[ei2]) && (edg_u[ei1] != edg_v[ei2]) && (edg_v[ei1] != edg_u[ei2]) && (edg_v[ei1] != edg_v[ei2]))
      {
        //std::cout << addr_to_id[&(*e1)] << " intersects " << addr_to_id[&(*e2)] << std::endl;
        //std::cout << "[" << *e1 << "] intersects " << "[" << *e2 << "]" << std::endl;
        std::stringstream ss;
        ss << *e1;
        std::string s = ss.str();
        typedef boost::tokenizer<boost::char_separator<char> > Tok;
        boost::char_separator<char> sep; // default constructed
        Tok tok(s, sep);
        int i = 0;
        double num = 0;
        double den = 1;
        double sign = 1;
        std::string edg = "";
        for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        {
          //std::cout << *tok_iter << std::endl;
          //std::cout << (*tok_iter).size() << std::endl;
          if(*tok_iter=="-")
          {
            sign = -1;
            continue;
          }
          if(i%3==0)
          {
            num = sign * std::stod(*tok_iter);
            sign = 1;
          }
          if(i%3==2)den = den*std::stod(*tok_iter);
          if(i%3==2)
          {
            edg += std::to_string(num/den);
            if(i!=11) edg += ",";
          }
          i++;
        }
        //std::cout << edg << std::endl;
        std::stringstream ss2;
        ss2 << *e2;
        s = ss2.str();
        //typedef boost::tokenizer<boost::char_separator<char> > Tok;
        //boost::char_separator<char> sep; // default constructed
        Tok tok2(s, sep);
        i = 0;
        num = 0;
        den = 1;
        sign = 1;
        std::string edg2 = "";
        for(Tok::iterator tok_iter = tok2.begin(); tok_iter != tok2.end(); ++tok_iter)
        {
          //std::cout << *tok_iter << std::endl;
          //std::cout << (*tok_iter).size() << std::endl;
          if(*tok_iter=="-")
          {
            sign = -1;
            continue;
          }
          if(i%3==0)
          {
            num = sign * std::stod(*tok_iter);
            sign = 1;
          }
          if(i%3==2)den = std::stod(*tok_iter);
          if(i%3==2)
          {
            edg2 += std::to_string(num/den);
            if(i!=11) edg2 += ",";
          }
          i++;
        }
        //std::cout << edg2 << std::endl;
        //std::cout << pnts_to_id[edg] << " intersects " << pnts_to_id[edg2] << std::endl;

        res_set[pnts_to_id[edg]].insert(pnts_to_id[edg2]);
        res_set[pnts_to_id[edg2]].insert(pnts_to_id[edg]);
      }
      //std::cout << "[" << eit->curve() << "]. Originating curves: ";
      /*for (ocit = arr.originating_curves_begin(eit);
         ocit != arr.originating_curves_end(eit); ++ocit)
        std::cout << " [" << *ocit << "]" << std::flush;
        std::cout << std::endl;*/
    }
    for (eit = arr.edges_begin(); eit != arr.edges_end(); ++eit) {
      Arr_with_hist_2::Curve_iterator e1 = arr.originating_curves_begin(eit->prev());
      Arr_with_hist_2::Curve_iterator e2 = arr.originating_curves_begin(eit);
      int ei1 = addr_to_id[&(*e1)];
      int ei2 = addr_to_id[&(*e2)];
      if((ei1 != ei2) && (edg_u[ei1] != edg_u[ei2]) && (edg_u[ei1] != edg_v[ei2]) && (edg_v[ei1] != edg_u[ei2]) && (edg_v[ei1] != edg_v[ei2]))
      {
        //std::cout << addr_to_id[&(*e1)] << " intersects " << addr_to_id[&(*e2)] << std::endl;
        //std::cout << "[" << *e1 << "] intersects " << "[" << *e2 << "]" << std::endl;
        std::stringstream ss;
        ss << *e1;
        std::string s = ss.str();
        typedef boost::tokenizer<boost::char_separator<char> > Tok;
        boost::char_separator<char> sep; // default constructed
        Tok tok(s, sep);
        int i = 0;
        double num = 0;
        double den = 1;
        double sign = 1;
        std::string edg = "";
        for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        {
          //std::cout << *tok_iter << std::endl;
          //std::cout << (*tok_iter).size() << std::endl;
          if(*tok_iter=="-")
          {
            sign = -1;
            continue;
          }
          if(i%3==0)
          {
            num = sign * std::stod(*tok_iter);
            sign = 1;
          }
          if(i%3==2)den = std::stod(*tok_iter);
          if(i%3==2)
          {
            edg += std::to_string(num/den);
            if(i!=11) edg += ",";
          }
          i++;
        }
        //std::cout << edg << std::endl;
        std::stringstream ss2;
        ss2 << *e2;
        s = ss2.str();
        //typedef boost::tokenizer<boost::char_separator<char> > Tok;
        //boost::char_separator<char> sep; // default constructed
        Tok tok2(s, sep);
        i = 0;
        num = 0;
        den = 1;
        sign = 1;
        std::string edg2 = "";
        for(Tok::iterator tok_iter = tok2.begin(); tok_iter != tok2.end(); ++tok_iter)
        {
          //std::cout << *tok_iter << std::endl;
          //std::cout << (*tok_iter).size() << std::endl;
          if(*tok_iter=="-")
          {
            sign = -1;
            continue;
          }
          if(i%3==0)
          {
            num = sign * std::stod(*tok_iter);
            sign = 1;
          }
          if(i%3==2)den = std::stod(*tok_iter);
          if(i%3==2)
          {
            edg2 += std::to_string(num/den);
            if(i!=11) edg2 += ",";
          }
          i++;
        }
        //std::cout << edg2 << std::endl;
        //std::cout << pnts_to_id[edg] << " intersects " << pnts_to_id[edg2] << std::endl;

        res_set[pnts_to_id[edg]].insert(pnts_to_id[edg2]);
        res_set[pnts_to_id[edg2]].insert(pnts_to_id[edg]);
      }
      //std::cout << "[" << eit->curve() << "]. Originating curves: ";
      /*for (ocit = arr.originating_curves_begin(eit);
         ocit != arr.originating_curves_end(eit); ++ocit)
        std::cout << " [" << *ocit << "]" << std::flush;
        std::cout << std::endl;*/
    }
    //return number_of_crossings;
    return res_set;
}
