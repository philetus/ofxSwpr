#pragma warning(disable : 4503)
#include "ofxBoostVoronoi.hpp"

namespace ofxSwpr {

    // generate triangle mesh for voronoi cell
    void Cll::mesh(ofVboMesh &msh, std::vector<glm::vec3>srcs, std::vector<glm::vec3> gens) {
        if (opn) return; // dont mesh open cells
        if (srcdx < 0) {
            ofLogError() << "meshing voronoi cell with unset source index!" << endl;
            return;
        }
        if (gendxs.size() < 3) {
            ofLogError() << "meshing voronoi cell with < 3 edges!" << endl;
            return;
        }

        // index of next vertex
        std::size_t vdx = msh.getNumVertices();

        // add center & get index
        msh.addVertex(srcs[srcdx]);
        std::size_t cntrdx = vdx++;

        // add first vertex & get index
        msh.addVertex(gens[gendxs[0]]);
        std::size_t frstdx = vdx++;

        std::size_t lstdx = frstdx;
        for (std::size_t i = 1; i < gendxs.size(); i++) {
            msh.addVertex(gens[gendxs[i]]); // add second vertex of edge

            // build triangle for each edge
            msh.addIndex(cntrdx);
            msh.addIndex(lstdx);
            msh.addIndex(vdx);
            lstdx = vdx++;
        }
        // add indexes for triangle from last to first vertex of cell
        msh.addIndex(cntrdx);
        msh.addIndex(lstdx);
        msh.addIndex(frstdx);
    }

    Swpr::Swpr() {}
    Swpr::~Swpr() {}

    void Swpr::addSource(double x, double y) {
        srcs.push_back(glm::vec3(x, y, 0));
    }

    void Swpr::update() {

        // clear everything except sources
        gens.clear();
        clls.clear();
        vrn.clear();
        dlny.clear();
        bvd.clear();

        // add point for each source
        std::vector<Point> pnts;
        for(long long i = 0; i < srcs.size(); i++)
            pnts.push_back(Point(srcs[i].x, srcs[i].y));

        // call boost diagram generator
        construct_voronoi(pnts.begin(), pnts.end(), &bvd);

        // build vector of generated voronoi vertices
        std::map<const voronoi_vertex<double> *, std::size_t> vrtmap;

        // iterate over boost diagram & generate vertices & cells
        for (voronoi_diagram<double>::const_cell_iterator cllitr = bvd.cells().begin(); 
                cllitr != bvd.cells().end(); 
                ++cllitr) {

            if(!cllitr->is_degenerate()) {
                Cll c = Cll(cllitr->source_index()); // init w/ index of source point

                // iterate over edges of cell and add index to initial vertex of each
                const voronoi_diagram<double>::edge_type *edg = cllitr->incident_edge();   
                if(edg != NULL){
                    do {
                        const voronoi_vertex<double> *vrtmap = edg->vertex0();
                            
                        // check for vertex in map
                        long long vvrtdx = -1;
                        if(vvrt != 0){
                            std::map<const voronoi_vertex<double> *, long long>::iterator vrtmapitr = vrtmap.find(vvrt);

                            // if pointer to voronoi vertex isnt in map 
                            // create vertex & add pointer to map with index
                            if(vrtmapitr == vrtmap.end()){
                                glm::vec3 v = glm::vec3(vvrt->x(), vvrt->y(), 0);
                                vvrtdx = (long long) vrts.size();
                                gens.push_back(v); // add to generated vertices
                                vrtmap[vvrt] = vvrtdx;
                            }
                            else { // if it is in map get index
                                vvrtdx = vrtmapitr->second;
                            }                   
                        }               
                        
                        // no vertex value for infinite segments, set open flag
                        if(vvrtdx == -1){
                            c.opn = true;
                        }
                        
                        // store index to vertex
                        c.gendxs.push_back(vvrtdx);
                        
                        // store index to neighboring cell
                        c.nbrdxs.push_back(edg->twin()->cell()->source_index());
                        
                        edg = edg->next();
                    } while (edg != cllitr->incident_edge() && edg != NULL);
                }

                clls.push_back(c);
            }
        }

        // build voronoi mesh
        vrn.setMode(OF_PRIMITIVE_TRIANGLES);

        // build triangles for each voronoi cell
        for (std::size_t i = 0; i < clls.size(); i++) {
            clls[i].mesh(vrn, srcs, gens);
        }
    }


    void Swpr::clear() {
        srcs.clear();
        gens.clear();
        clls.clear();
        vrn.clear();
        dlny.clear();
        bvd.clear();
    }

}